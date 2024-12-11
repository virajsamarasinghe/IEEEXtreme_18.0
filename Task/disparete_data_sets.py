import sys
import csv

def main():
    evts = []
    csv_rdr = csv.reader(sys.stdin, delimiter=',', quotechar='"')
    
    for row in csv_rdr:
        if len(row) != 6:
            continue
        ev_id, ev_title, acr, proj_code, three_code, rec_type = map(str.strip, row)

        if not acr:
            continue

        evt = {
            'ID': ev_id,
            'Title': ev_title,
            'Acr': acr,
            'Proj Code': proj_code,
            '3-Digit Code': three_code,
            'Type': rec_type,
        }
        evts.append(evt)

    grp_evt = {}
    for evt in evts:
        acr = evt['Acr']
        if acr not in grp_evt:
            grp_evt[acr] = []
        grp_evt[acr].append(evt)

    out = {}
    for acr in grp_evt:
        grp = grp_evt[acr]
        parent = [ev for ev in grp if ev['Type'] == 'Parent Event']
        children = [ev for ev in grp if ev['Type'] == 'IEEE Event']
        
        if len(parent) != 1:
            continue

        p_evt = parent[0]
        if not children:
            continue
        
        uniq_codes = set(child['3-Digit Code'] for child in children)
        p_evt['3-Digit Code'] = uniq_codes.pop() if len(uniq_codes) == 1 else '???'

        for child in children:
            child['Parent ID'] = p_evt['ID']
        
        children.sort(key=lambda e: (e['Title'], e['ID']))
        
        out[acr] = {'parent': p_evt, 'children': children}

    for acr in sorted(out.keys()):
        grp = out[acr]
        p_evt = grp['parent']
        c_evts = grp['children']
        
        print_evt(p_evt)
        
        for child in c_evts:
            print_evt(child, parent_id=child['Parent ID'])

def print_evt(evt, parent_id=None):
    out = [
        evt['ID'],
        '"{}"'.format(evt['Title'].replace('"', '""')),
        '"{}"'.format(evt['Acr']),
        evt['Proj Code'],
        evt['3-Digit Code'],
        '"{}"'.format(evt['Type']),
    ]
    if parent_id is not None:
        out.append(parent_id)
    print(','.join(out))

if __name__ == '__main__':
    main()
