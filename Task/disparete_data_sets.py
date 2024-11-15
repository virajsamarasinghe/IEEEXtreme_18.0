import sys
import csv

def main():
    events = []
    csv_reader = csv.reader(sys.stdin, delimiter=',', quotechar='"')
    
    for row in csv_reader:
        if len(row) != 6:
            continue
        event_id = row[0].strip()
        event_title = row[1].strip()
        acronym = row[2].strip()
        project_code = row[3].strip()
        three_digit_code = row[4].strip()
        record_type = row[5].strip()

        if not acronym:
            continue

        event_details = {
            'Event ID': event_id,
            'Event Title': event_title,
            'Acronym': acronym,
            'Project Code': project_code,
            '3 Digit Project Code': three_digit_code,
            'Record Type': record_type,
        }
        events.append(event_details)

    grouped_events = {}
    for event in events:
        event_acronym = event['Acronym']
        if event_acronym not in grouped_events:
            grouped_events[event_acronym] = []
        grouped_events[event_acronym].append(event)

    organized_output = {}
    for acronym in grouped_events:
        event_group = grouped_events[acronym]
        parent_events = [evt for evt in event_group if evt['Record Type'] == 'Parent Event']
        child_events = [evt for evt in event_group if evt['Record Type'] == 'IEEE Event']
       
        if len(parent_events) != 1:
            continue
       
        parent_event = parent_events[0]
       
        if not child_events:
            continue
       
        unique_child_codes = set(child['3 Digit Project Code'] for child in child_events)
        if len(unique_child_codes) == 1:
            parent_event['3 Digit Project Code'] = unique_child_codes.pop()
        else:
            parent_event['3 Digit Project Code'] = '???'
       
        for child in child_events:
            child['Parent ID'] = parent_event['Event ID']
       
        child_events.sort(key=lambda evt: (evt['Event Title'], evt['Event ID']))
       
        organized_output[acronym] = {
            'parent': parent_event,
            'children': child_events
        }

    for acronym in sorted(organized_output.keys()):
        group = organized_output[acronym]
        parent_event = group['parent']
        child_events = group['children']
       
        print_event_details(parent_event)
       
        for child in child_events:
            print_event_details(child, parent_id=child['Parent ID'])

def print_event_details(event, parent_id=None):
    output = [
        event['Event ID'],
        '"{}"'.format(event['Event Title'].replace('"', '""')),
        '"{}"'.format(event['Acronym']),
        event['Project Code'],
        event['3 Digit Project Code'],
        '"{}"'.format(event['Record Type']),
    ]
    if parent_id is not None:
        output.append(parent_id)
    print(','.join(output))

if __name__ == '__main__':
    main()
#100%marks