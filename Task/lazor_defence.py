import bisect

line_length, num_first_commands, num_second_commands = map(int, input().split())

first_positions = []
second_positions = []

total_sections = num_first_commands + 1

for _ in range(num_first_commands):
    direction, position = input().split()
    position = int(position)
    if direction == 'U':
        first_positions.append(position)
    elif direction == 'R':
        first_positions.append(line_length)
    elif direction == 'L':
        first_positions.append(0)

for _ in range(num_second_commands):
    direction, position = input().split()
    position = int(position)
    if direction == 'U':
        second_positions.append(position)
    elif direction == 'R':
        second_positions.append(line_length)
    elif direction == 'L':
        second_positions.append(0)

first_positions.sort()

for position in second_positions:
    overlaps = len(first_positions) - bisect.bisect_right(first_positions, position)
    total_sections += overlaps + 1

print(total_sections)
#100% marks