# Weight Release Calculator for Version Library Tests:
# ---------------------------------------------------------
# This script contains some mathematical equations tests
# to verify the best approach to create a multipurpose weight
# system for build release components, specially the semantic
# versioning composed releases, like alpha.beta, alpha.2.beta.3,
# etc.
# 
# The used mathematical approach resolves the composed releases
# creating a weight for each release and using them in arithmetic
# mean. This approach may not be perfect, specially where has
# a lot of release components together. This situation is almost
# impossible, considering the semantic versioning recommendations
# to not exceed 255 characters
# (https://semver.org/#does-semver-have-a-size-limit-on-the-version-string)
#
# Benefits of this methodology:
# 
# Using this mathematical method can allows developers to use
# custom release and pre-release information with their own
# weights to create different approaches.
# 
# This also reduces the chances to get a bug on the code to
# check for the lower, higher or equal version release
# information on custom classes.
#
# NOTES ABOUT THIS SCRIPT EXAMPLE:
# ---------------------------------------------------------
# This scripts does not contain a specific release information
# like "alpha.beta.1". It uses a generic approach to bring a
# good example on how this methodology can be useful.
#

import math

calcMean = 1

class ver:
    build = 0
    rev = 0

    def __init__(self, build, rev = 0):
        self.build = build
        self.rev = rev
        pass

    def weight(self, pos = 1) -> float:
        val = 0.0
        val = math.pow(((self.rev + 1) / math.pow(pos, -1)), (1 / self.build))
        if val == 1:
            val = 0
            pass
        val = math.log(math.pow(self.build, self.build) + val, self.build)
        return val

def calcWeights(mylist: list[ver]) -> float:
    global calcMean

    val = 0.0
    i = 0

    # No mean:
    if calcMean == 0:
        while i < len(mylist):
            tmp = mylist[i]
            val += tmp.weight(i + 1)
            i += 1
            pass
        return val

    # Arithmetic mean:
    if calcMean == 1:
        while i < len(mylist):
            tmp = mylist[i]
            val += tmp.weight(i + 1)
            i += 1
            pass
        return val / len(mylist)
    
    # Harmonic mean:
    if calcMean == 2:
        while i < len(mylist):
            tmp = mylist[i]
            val += math.pow(tmp.weight(i + 1), -1)
            i += 1
            pass
        return len(mylist) / val
    return val

a    = calcWeights([ver(2, 0)])
a1   = calcWeights([ver(2, 1)])
a2   = calcWeights([ver(2, 2)])
ab   = calcWeights([ver(2, 0), ver(3, 0)])
ab1  = calcWeights([ver(2, 0), ver(3, 1)])
a1b  = calcWeights([ver(2, 1), ver(3, 0)])
a1b1 = calcWeights([ver(2, 1), ver(3, 1)])
b    = calcWeights([ver(3, 0), ver(2, 0), ver(4, 0)])
ac   = calcWeights([ver(2, 0), ver(4, 0)])
abc  = calcWeights([ver(2, 0), ver(3, 0), ver(4, 0)])
b1   = calcWeights([ver(3, 1)])
b2   = calcWeights([ver(3, 2)])
abcd = calcWeights([ver(2, 0), ver(3, 0), ver(4, 0), ver(5, 0)])
c    = calcWeights([ver(4, 0)])
c1   = calcWeights([ver(4, 1)])
c2   = calcWeights([ver(4, 2)])
c3   = calcWeights([ver(4, 3)])
cd   = calcWeights([ver(4, 0), ver(5, 0)])
d    = calcWeights([ver(5, 0)])
d1   = calcWeights([ver(5, 1)])

print(f"a        = {a}")
print(f"a.1      = {a1}")
print(f"a.2      = {a2}")
print(f"a.b      = {ab}")
print(f"a.b.1    = {ab1}")
print(f"a.1.b    = {a1b}")
print(f"a.1.b.1  = {a1b1}")
print(f"b        = {b}")
print(f"a.c      = {ac}")
print(f"a.b.c    = {abc}")
print(f"b1.      = {b1}")
print(f"b.2      = {b2}")
print(f"a.b.c.d  = {abcd}")
print(f"c        = {c}")
print(f"c.1      = {c1}")
print(f"c.2      = {c2}")
print(f"c.3      = {c3}")
print(f"c.d      = {cd}")
print(f"d        = {d}")
print(f"d.1      = {d1}")
