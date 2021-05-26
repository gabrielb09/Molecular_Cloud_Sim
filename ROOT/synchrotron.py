import numpy as np
from naima.models import Synchrotron
import astropy.units as u
from scipy import interpolate
import sys

B = float(sys.argv[1])*u.uG

inFile_name = sys.argv[2]

e_min = float(sys.argv[3])
e_max = float(sys.argv[4])
nbins = int(sys.argv[5])

outFile_name = sys.argv[6]

def T(E):
    t = (1.3e5)*((E.to('TeV').value)**(-1))*((B/(10*u.uG))**(-2))*u.yr
    return t.to('s')


bins = []
counts = []

with open(inFile_name, 'r') as infile:
    next(infile)
    for line in infile:
        binC, count = line.split()
        bins.append(float(binC))
        counts.append(float(count))

bins = np.array(bins)
counts = np.array(counts)

dE = bins[1] - bins[0]

e_dens = counts/dE

interp_dist = interpolate.interp1d(bins, e_dens, kind = 'nearest', fill_value = "extrapolate")

def electron_dist(E):
    E = E.to(u.MeV)
    return interp_dist(E)*(1/u.MeV)

E = np.linspace(e_min, e_max, nbins)*u.MeV
print(E)
Gamma_Counts = np.zeros(len(E))

for count, bin_center in zip(counts,bins):
    if count != 0:
        bin_min = (bin_center - dE/2)*u.MeV
        bin_max = (bin_center + dE/2)*u.MeV

        SYN = Synchrotron(electron_dist, B = B, Eemin = bin_min, Eemax = bin_max)

        flux = SYN.flux(E, distance = 0)
        photo_counts = flux*(E[1] - E[0])
        photo_counts = photo_counts.to("1/s")

        photo_counts *= T(bin_center*u.MeV)

        Gamma_Counts += photo_counts.value

with open(outFile_name, 'w+') as outFile:
    for e, c in zip(E, Gamma_Counts):
        outFile.write('{} {}\n'.format(e.value, c))
