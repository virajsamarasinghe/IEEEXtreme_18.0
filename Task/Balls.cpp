def count_hit_tiles(total_tiles, num_elasticities, elasticities):
    if 1 in elasticities:
        return total_tiles

    elasticities = [e for e in elasticities if e <= total_tiles]
    num_elasticities = len(elasticities)

    if num_elasticities == 0:
        return 0

    elasticities.sort()
    hit_count = 0

    def recurse(index, current_product, sign):
        nonlocal hit_count
        for i in range(index, num_elasticities):
            elasticity = elasticities[i]
            new_product = current_product * elasticity
            if new_product > total_tiles:
                break
            hit_count += sign * (total_tiles // new_product)
            recurse(i + 1, new_product, -sign)

    recurse(0, 1, 1)
    return hit_count

if __name__ == "__main__":
    import sys

    input_data = sys.stdin.read().split()
    total_tiles = int(input_data[0])
    num_elasticities = int(input_data[1])
    elasticities = list(map(int, input_data[2:2 + num_elasticities]))

    print(count_hit_tiles(total_tiles, num_elasticities, elasticities))




//100% marks