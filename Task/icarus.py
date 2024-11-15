def sprout_shrubbery(spell_cast):
    max_shrubs = 2 * len(spell_cast)
    twig_left = [0] * (max_shrubs + 1)
    twig_right = [0] * (max_shrubs + 1)
    for pixie_dust in range(1, max_shrubs + 1):
        twig_left[pixie_dust] = 2 * pixie_dust if 2 * pixie_dust <= max_shrubs else 0
        twig_right[pixie_dust] = 2 * pixie_dust + 1 if 2 * pixie_dust + 1 <= max_shrubs else 0
    return twig_left, twig_right, max_shrubs

def dance_through_forest(spell_cast, start_shrub, twig_left, twig_right):
    enchanted_shrub = start_shrub
    shrub_footprints = set()
    shrub_footprints.add(enchanted_shrub)
    for step in spell_cast:
        if step == 'L':
            next_shrub = twig_left[enchanted_shrub]
        elif step == 'R':
            next_shrub = twig_right[enchanted_shrub]
        elif step == 'U':
            next_shrub = enchanted_shrub // 2
        else:
            continue
        if next_shrub != 0:
            enchanted_shrub = next_shrub
            shrub_footprints.add(enchanted_shrub)
    return shrub_footprints

def grand_adventure():
    import sys
    input_spell = sys.stdin.read
    spell_cast = input_spell().strip()
    twig_left, twig_right, forest_shrubs = sprout_shrubbery(spell_cast)
    magical_start = 2
    shrub_footprints = dance_through_forest(spell_cast, magical_start, twig_left, twig_right)
    for final_shrub in range(1, forest_shrubs + 1):
        if final_shrub not in shrub_footprints:
            break
    else:
        print(-1)
        return
    print(forest_shrubs, magical_start, final_shrub)
    for gnome_shrub in range(1, forest_shrubs + 1):
        print(twig_left[gnome_shrub], twig_right[gnome_shrub])

if __name__ == "__main__":
    grand_adventure()
    
    
#100% marks    
    