#!/usr/bin/env python3

from math import sqrt
import matplotlib.pyplot as plt

z_max = 50  # Starting height
z = z_max  # Current height
g = 9.81  # m/s/s
t = 0  # starting time
t_max = sqrt(2 * z_max / g)
print(t_max)
v_max = g * t_max
print(v_max)
v = 0  # m/s, current velocity
dt = 0.001  # time step
a = 0
H = []
T = []
V = []
A = []
while z > 0:
    z = z - v * dt - 0.5 * g * dt * dt
    print("Height", z)
    t = t + dt
    print("Time", t)
    v = v + g * dt
    print("Speed", v)
    a = v/t
    print("Acceleration", v)
    H.append(z)
    T.append(t)
    V.append(v)
    A.append(a)

fig = plt.figure()
plt.plot(T, H, label='Height at time')
plt.plot(T, V, label='Velocity')
plt.plot(T, A, label='Acceleration')
plt.xlabel('Time in seconds')
plt.ylabel('Height in metres')
plt.title('Free Falling')
plt.legend()
fig.savefig("Free Fall v and a.png")
plt.show()
