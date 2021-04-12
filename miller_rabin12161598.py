"""
miller-rabin prime test

Test if n is prime with error probability less than 2^(−𝑠).

"""

import random
from exponentiation import exp

Prime = 0
Composite = 1


def miller_rabin(n, s):
    if n == 2:
        return Prime
    elif n % 2 == 0:
        return Composite

    for _ in range(s):
        a = random.randint(1, n-1)
        if test(a, n) == True:
            return Composite

    return Prime


def int_to_bin(num):
    return list(bin(num))[2:]


def test(a, n):
     # n-1을 인수분해
     t=0
     nn=n-1
     while((nn%2) == 0):
         t+=1
         nn//=2
     u=nn
#     print("a : ", a, "n : ", n, "u: ", u, "t: ", t)
     # t=1 부터 n까지 a^u를 거듭제곱하면서 NSR test
     x_0=0
     x_i = exp(a,u,n)
     for i in range(t):
#         print("x_0 : ", x_0, "x_i : ", x_i)
         if(x_i == 1 or x_i== (n-1)):
             return False # prime이라는 증거
         x_0=x_i
         x_i=exp(x_i,2,n)
     return True # composite이다.

if __name__ == "__main__":

    primes = [
        39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112319,
        6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151,
        443372888629441, 561
    ]

    for p in primes:
        result = miller_rabin(p, 20)
        if result == Prime:
            print("Prime")
        elif result == Composite:
            print("Composite")
        else:
            print("Undefined")
