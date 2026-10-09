import Debug
import Math
import Containers

vi = Containers.Vector_float()

vi.push(1.5)
vi.push(2.5)
vi.push(3.5)
vi.push(4.5)
vi.push(5.5)

def print_vec(_vi):
    for i in range(_vi.size()):
        print(_vi[i]);

print_vec(vi)
