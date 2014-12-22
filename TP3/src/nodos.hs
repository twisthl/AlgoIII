main = print (f 6) 

f::Int->Int
f n = g n 1

g::Int->Int->Int
g 1 c = 1
g h c = ((g (h-1) c) * c) + (g (h-1) (c+1)) + 1

num::Int->Int
num 1 = 1