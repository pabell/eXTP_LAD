import matplotlib.pyplot as plt
import numpy as np
import matplotlib.font_manager as fm
prop = fm.FontProperties(size=11)
from scipy import interpolate

from myUtilities import prettifyPlot
prettifyPlot()

version = '6.0'


"""
We assume:
a. uniform 4pi distribution for secondary particles
b. uniform distribution on the visible (not Earth-blocked) sky for primary particles and leakage CXB
c. for albedo gamma rays: uniform distribution on the earth solid angle
""" 

def solid_angle(h):
	"""
	Solid angle subtended by the Earth at
	height h in km
	"""
	R_e = 6378. # Earth radius
	eps = R_e/h
	omega = 2*np.pi*(1 - (1/(eps+1))*np.sqrt(1+2*eps))
	return omega

def theta_cut(h):
	"""
	Maximum zenital angle for an height of h km
	(Earth horizon)
	"""
	R_e = 6378. # Earth radius
	theta = np.degrees(np.arcsin(1/(h/R_e + 1.)))
	return 180. - theta

	
	
# Effective sky exposure, accounting for Earth blockage
earth_block = 1 - solid_angle(600.)/(4*np.pi)
print "Visible fraction of the sky: %.3f" % earth_block
print "Earth horizon at: %.1f degrees" %  theta_cut(600.)


fig = plt.figure()
ax = fig.add_subplot(111)


binsize = 1.0
i_2  = 1
i_10 = 9
i_30 = 29
i_50 = 49
i_80 = 79


# Direct CXB, to be verified...
x_cxb, y_cxb, erry_cxb = np.loadtxt("spectrum_directCXB_1e7_1keVbins.dat", unpack=True)
omega_corrected = 1.
y_cxb = y_cxb*omega_corrected
erry_cxb = erry_cxb*omega_corrected
plt.loglog(x_cxb, y_cxb, drawstyle='steps-mid', label="Aperture CXB", color='green')
plt.errorbar(x_cxb, y_cxb, yerr=erry_cxb, drawstyle='steps-mid', capsize=0, color='green')


print "Aperture CXB count rate 2-30 keV: %.1e counts/cm^2/s"  % (np.sum(y_cxb[i_2:i_30])*binsize)
print "Aperture CXB count rate 2-10 keV: %.1e counts/cm^2/s"  % (np.sum(y_cxb[i_2:i_10])*binsize)
print "Aperture CXB count rate 10-30 keV: %.1e counts/cm^2/s" % (np.sum(y_cxb[i_10:i_30])*binsize)
print "Aperture CXB count rate 30-50 keV: %.1e counts/cm^2/s" % (np.sum(y_cxb[i_30:i_50])*binsize)
print "Aperture CXB count rate 2-50 keV: %.1e counts/cm^2/s"  % (np.sum(y_cxb[i_2:i_50])*binsize)



# Leakage CXB
x, y_leak, erry_leak = np.loadtxt("spectrum_leakageCXB_1e8.dat", unpack=True)
y_leak    *= earth_block
erry_leak *= earth_block
plt.loglog(x, y_leak, drawstyle='steps-mid', label="Leakage CXB", color='magenta')
plt.errorbar(x, y_leak, yerr=erry_leak, drawstyle='steps-mid', capsize=0, color='magenta')


print "Leakage CXB count rate 2-30 keV: %.1e counts/cm^2/s"  % (np.sum(y_leak[i_2:i_30])*binsize)
print "Leakage CXB count rate 2-10 keV: %.1e counts/cm^2/s"  % (np.sum(y_leak[i_2:i_10])*binsize)
print "Leakage CXB count rate 10-30 keV: %.1e counts/cm^2/s" % (np.sum(y_leak[i_10:i_30])*binsize)
print "Leakage CXB count rate 30-50 keV: %.1e counts/cm^2/s" % (np.sum(y_leak[i_30:i_50])*binsize)
print "Leakage CXB count rate 2-50 keV: %.1e counts/cm^2/s"  % (np.sum(y_leak[i_2:i_50])*binsize)


print
# Albedo gamma-rays
x, y_alb, erry_alb = np.loadtxt("spectrum_albedo_1e8.dat", unpack=True)
y_alb    *= 1-earth_block
erry_alb *= 1-earth_block
plt.loglog(x, y_alb, drawstyle='steps-mid', label="Albedo $\\gamma$-rays", color='orange')
plt.errorbar(x, y_alb, yerr=erry_alb, drawstyle='steps-mid', capsize=0, color='orange')

print "Albedo gamma-ray count rate 2-30 keV: %.1e counts/cm^2/s"  % (np.sum(y_alb[i_2:i_30])*binsize)
print "Albedo gamma-ray count rate 2-10 keV:  %.1e counts/cm^2/s" % (np.sum(y_alb[i_2:i_10])*binsize)
print "Albedo gamma-ray count rate 10-30 keV: %.1e counts/cm^2/s" % (np.sum(y_alb[i_10:i_30])*binsize)
print "Albedo gamma-ray count rate 30-50 keV: %.1e counts/cm^2/s" % (np.sum(y_alb[i_30:i_50])*binsize)
print "Albedo gamma-ray count rate 2-50 keV: %.1e counts/cm^2/s"  % (np.sum(y_alb[i_2:i_50])*binsize)


print
# Primary protons
x, y_pp, erry_pp = np.loadtxt("spectrum_primaryProtons_1e6.dat", unpack=True)
y_pp    *= earth_block
erry_pp *= earth_block
# plt.loglog(x, y_pp, drawstyle='steps-mid', label="Primary protons", color='black')
# plt.errorbar(x, y_pp, yerr=erry_pp, drawstyle='steps-mid', capsize=0, color='black')

print "Primary protons count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_pp[i_2:i_30])*binsize)
print "Primary protons count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_pp[i_2:i_10])*binsize)
print "Primary protons count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_pp[i_10:i_30])*binsize)
print "Primary protons count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_pp[i_30:i_50])*binsize)
print "Primary protons count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_pp[i_2:i_50])*binsize)


# Primary electrons
x, y_pem, erry_pem = np.loadtxt("spectrum_primaryElectrons_1e6.dat", unpack=True)
y_pem    *= earth_block
erry_pem *= earth_block
# plt.loglog(x, y_pem, drawstyle='steps-mid', label="Primary electrons", color='red')
# plt.errorbar(x, y_pem, yerr=erry_pem, drawstyle='steps-mid', capsize=0, color='red')

print "Primary electrons count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_pem[i_2:i_30])*binsize)
print "Primary electrons count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_pem[i_2:i_10])*binsize)
print "Primary electrons count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_pem[i_10:i_30])*binsize)
print "Primary electrons count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_pem[i_30:i_50])*binsize)
print "Primary electrons count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_pem[i_2:i_50])*binsize)


# Primary positrons
x, y_pep, erry_pep = np.loadtxt("spectrum_primaryPositrons_1e6.dat", unpack=True)
y_pep   *= earth_block
erry_pep *= earth_block
# plt.loglog(x, y_pep, drawstyle='steps-mid', label="Primary positrons", color='yellow')
# plt.errorbar(x, y_pep, yerr=erry_pep, drawstyle='steps-mid', capsize=0, color='yellow')

print "Primary positrons count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_pep[i_2:i_30])*binsize)
print "Primary positrons count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_pep[i_2:i_10])*binsize)
print "Primary positrons count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_pep[i_10:i_30])*binsize)
print "Primary positrons count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_pep[i_30:i_50])*binsize)
print "Primary positrons count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_pep[i_2:i_50])*binsize)

# Primary alpha
x, y_pa, erry_pa = np.loadtxt("spectrum_primaryAlpha_1e6.dat", unpack=True)
y_pa   *= earth_block
erry_pa *= earth_block
# plt.loglog(x, y_pep, drawstyle='steps-mid', label="Primary positrons", color='yellow')
# plt.errorbar(x, y_pep, yerr=erry_pep, drawstyle='steps-mid', capsize=0, color='yellow')

print "Primary alpha count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_pa[i_2:i_30])*binsize)
print "Primary alpha count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_pa[i_2:i_10])*binsize)
print "Primary alpha count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_pa[i_10:i_30])*binsize)
print "Primary alpha count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_pa[i_30:i_50])*binsize)
print "Primary alpha count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_pa[i_2:i_50])*binsize)


print
# Secondary protons 
x, y_sp, erry_sp = np.loadtxt("spectrum_secondaryProtons_1e6.dat", unpack=True)
# plt.loglog(x, y_sp, drawstyle='steps-mid', label="Secondary protons", color='blue')
# plt.errorbar(x, y_sp, yerr=erry_sp, drawstyle='steps-mid', capsize=0, color='blue')

print "Secondary protons count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_sp[i_2:i_30])*binsize)
print "Secondary protons count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_sp[i_2:i_10])*binsize)
print "Secondary protons count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_sp[i_10:i_30])*binsize)
print "Secondary protons count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_sp[i_30:i_50])*binsize)
print "Secondary protons count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_sp[i_2:i_50])*binsize)


# Secondary electrons 
x, y_sem, erry_sem = np.loadtxt("spectrum_secondaryElectrons_1e6.dat", unpack=True)
# plt.loglog(x, y_sem, drawstyle='steps-mid', label="Secondary electrons", color='orange')
# plt.errorbar(x, y_sem, yerr=erry_sem, drawstyle='steps-mid', capsize=0, color='orange')

print "Secondary electrons count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_sem[i_2:i_30])*binsize)
print "Secondary electrons count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_sem[i_2:i_10])*binsize)
print "Secondary electrons count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_sem[i_10:i_30])*binsize)
print "Secondary electrons count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_sem[i_30:i_50])*binsize)
print "Secondary electrons count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_sem[i_2:i_50])*binsize)


# Secondary positrons 
x, y_sep, erry_sep = np.loadtxt("spectrum_secondaryPositrons_1e6.dat", unpack=True)
# plt.loglog(x, y_sep, drawstyle='steps-mid', label="Secondary positrons", color='cyan')
# plt.errorbar(x, y_sep, yerr=erry_sep, drawstyle='steps-mid', capsize=0, color='cyan')

print "Secondary positrons count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_sep[i_2:i_30])*binsize)
print "Secondary positrons count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_sep[i_2:i_10])*binsize)
print "Secondary positrons count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_sep[i_10:i_30])*binsize)
print "Secondary positrons count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_sep[i_30:i_50])*binsize)
print "Secondary positrons count rate 2-50 keV: %.1e counts/cm^2/s" % (np.sum(y_sep[i_2:i_50])*binsize)


print
y_particle = y_sp + y_sem + y_sep + y_pa + y_pp + y_pem + y_pep
erry_particle = np.sqrt( erry_sp**2 + erry_sem**2 + erry_sep**2 + erry_pa**2 + erry_pp**2 + erry_pem**2 + erry_pep**2)
plt.loglog(x, y_particle, drawstyle='steps-mid', label="Particle ($p, e^\\pm, \\alpha$)", color='red')
plt.errorbar(x, y_particle, yerr=erry_particle, drawstyle='steps-mid', capsize=0, color='red')

print "Total particle count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_particle[i_2:i_30])*binsize)
print "Total particle count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_particle[i_2:i_10])*binsize)
print "Total particle count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_particle[i_10:i_30])*binsize)
print "Total particle count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_particle[i_30:i_50])*binsize)
print "Total particle count rate  2-50 keV %.1e counts/cm^2/s" % (np.sum(y_particle[i_2:i_50])*binsize)
print

# Albedo neutrons 
x, y_neu, erry_neu = np.loadtxt("spectrum_neutronAlbedo_1e8.dat", unpack=True)
y_neu    *= 1-earth_block
erry_neu *= 1-earth_block
plt.loglog(x, y_neu, drawstyle='steps-mid', label="Albedo neutrons", color='cyan')
plt.errorbar(x, y_neu, yerr=erry_neu, drawstyle='steps-mid', capsize=0, color='cyan')

print "Neutron albedo count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_neu[i_2:i_30])*binsize)
print "Neutron albedo count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_neu[i_2:i_10])*binsize)
print "Neutron albedo count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_neu[i_10:i_30])*binsize)
print "Neutron albedo count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_neu[i_30:i_50])*binsize)
print "Neutron albedo count rate  2-50 keV %.1e counts/cm^2/s" % (np.sum(y_neu[i_2:i_50])*binsize)
print


# 40K EC 
x_40K, y_40K, erry_40K = np.loadtxt("spectrum_40K_1e7_1keVbins.dat", unpack=True)
plt.loglog(x_40K, y_40K, drawstyle='steps-mid', label="$^{40}$K activity", color='blue')
plt.errorbar(x_40K, y_40K, yerr=erry_40K, drawstyle='steps-mid', capsize=0, color='blue')

print "40K activity count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_40K[i_2:i_30])*binsize)
print "40K activity count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_40K[i_2:i_10])*binsize)
print "40K activity count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_40K[i_10:i_30])*binsize)
print "40K activity count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_40K[i_30:i_50])*binsize)
print "40K activity count rate  2-50 keV %.1e counts/cm^2/s" % (np.sum(y_40K[i_2:i_50])*binsize)



#print len(y_leak), len(y_particle), len(y_alb), len(y_neu), len(y_cxb), len(y_40K)
print

area_eff = 100000
oar = 0.694
area = area_eff/oar


y_total = y_leak + y_particle + y_alb + y_neu + y_cxb*oar + y_40K

erry_total = np.sqrt(erry_leak**2 + erry_particle**2 + erry_alb**2 + erry_neu**2 + erry_40K**2)
plt.loglog(x, y_total, drawstyle='steps-mid', label="Total background", color='black')
plt.errorbar(x, y_total, yerr=erry_total, drawstyle='steps-mid', capsize=0, color='black')


print "Total background count rate 2-30 keV: %.1e counts/cm^2/s" % (np.sum(y_total[i_2:i_30])*binsize)
print "Total background count rate 2-10 keV: %.1e counts/cm^2/s" % (np.sum(y_total[i_2:i_10])*binsize)
print "Total background count rate 10-30 keV %.1e counts/cm^2/s" % (np.sum(y_total[i_10:i_30])*binsize)
print "Total background count rate 30-50 keV %.1e counts/cm^2/s" % (np.sum(y_total[i_30:i_50])*binsize)
print "Total background count rate 2-50 keV %.1e counts/cm^2/s"  % (np.sum(y_total[i_2:i_50])*binsize)
print "Total background count rate 2-80 keV %.1e counts/cm^2/s"  % (np.sum(y_total[i_2:i_80])*binsize)
print "Total background count rate 2-** keV %.1e counts/cm^2/s"  % (np.sum(y_total[i_2:])*binsize)


# np.savetxt("total_background_lite_LSv4.5.dat", zip(x, y_total), fmt="%.4e %.4e")

x, dx, y, dy, modello = np.loadtxt("crab.dat", unpack=True)
y = y*0.01/area_eff
plt.plot(x, y, '--', label="10 mCrab", color='black')

plt.xlim(2,60)
plt.ylim(1e-6,1e-1)
plt.xlabel("Energy (keV)", fontsize=16)
plt.ylabel("Counts cm$^{-2}$ s$^{-1}$ keV$^{-1}$", fontsize=16)
plt.legend(prop=prop)
ax.set_xticks([2,3,5,10,20,30,50,60])
ax.set_xticklabels([2,3,5,10,20,30,50,60])

plt.title("LoftSIM v%s - LOFT LAD Background" % version)
plt.savefig("bkg_v%s.pdf" % version)
plt.show()