
from random import random
from time import perf_counter
from Doves_and_Hawks import first_Problem
from Doves_and_Hawks import second_Problem





COUNT = 500000  # Change this value depending on the speed of your computer
DATA = [(random() - 0.5) * 3 for _ in range(COUNT)]

def test(fn, name):
    start = perf_counter()
    result = fn(DATA)
    duration = perf_counter() - start
    print('{} took {:.3f} seconds\n\n'.format(name, duration))
    

    for d in result:
        assert -1 <= d <= 1, " incorrect values"




if __name__ == "__main__":


    print("Run Hawks V Doves sim 1 ")
    print(first_Problem(0))
    print("Run Hawks V Doves sim 2 ")
    print(second_Problem(0))

    sim1= pd.read_csv('/Doves_and_Hawks/Doves_Hawks1')
    sim2= pd.read_csv('/Doves_and_Hawks/Doves_Hawks2')
    print(sim1.head())








