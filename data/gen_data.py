from random import choice
from collections import namedtuple


Country = namedtuple('Country', ['name', 'pop', 'code'])


def create_file(country: Country, groups: list):
    lines = []
    for _ in range(country.pop):
        g = choice(groups)
        lines.append(f'{g}\n')

    filename = f'{country.code}.txt'
    with open(filename, 'w') as f:
        f.writelines(lines)


# Data about population is from
# https://worldpopulationreview.com/continents/western-africa-population
countries = [
    Country('Benin', 12_794_780, 'bj'),
    Country('Burkina Faso', 22_121_109, 'bf'),
    Country('Niger', 26_112_425, 'ne'),
    Country('Togo', 8_686_953, 'tg'),
]

groups = ['A', 'AB', 'B', 'O']

for country in countries:
    print(f'Generating data for {country.name}...')
    create_file(country, groups)
print('Done.')
