import matplotlib.pyplot as plt
import numpy as np
try:
    import astropy.io.fits as pyfits 
except:
    import pyfits
import sys
import os
import matplotlib.font_manager as fm

def find_key(dic, val):
    """return the key of dictionary dic given the value"""
    return [k for k, v in dic.iteritems() if v == val]

filein       = sys.argv[1]
filename, ext = os.path.splitext(filein)
if ext == ".gz":
    filename = os.path.splitext(filename)[0]
fileout      =  filename + "_filtered.fits"

print filename

# Binning of the resulting spectrum (in keV)
newbinsize = 1.0
N_primaries = float(filein.split(".")[0].split("_")[1])

hdulist   = pyfits.open(filein)
hdr       = hdulist[1].header
data      = hdulist[1].data
eventid   = data.field("EventID")
endep     = data.field("En_dep")
X_ID      = data.field("X_ID")
Y_ID      = data.field("Y_ID")
theta     = data.field("Theta_Primary")
phi       = data.field("Phi_Primary")
hdulist.close()

# Initialize output arrays
eventid_out   = []
endep_out     = []
theta_out     = []
phi_out       = []
endep_s = []
endep_m = []

N_detected = len(endep)
# print "Number of detector counts:", N_detected
# print "Efficiency", N_detected/float(N_primaries)

set_events = sorted(set(eventid))
N_uniqueEvts = len(set_events)
# print "Number of unique primary events detected:", N_uniqueEvts

# # Identify module ID for each event
# m_ID = np.zeros(N_detected, dtype=int)
# for i in xrange(N_detected):
#   m_x = np.floor(X_ID[i]/500.)
#   m_y = np.floor(Y_ID[i]/8.)
#   m_ID[i] = int(m_x + 7*m_y)



# Fill dictionary with event multiplicity
# key: event ID
# value: number of pixels
if sys.version < '2.7':
	print 'Older Python Version !!!'
	print 'The code will run slower and will be limited to max 1e8 evts.'
	evt_topology_dict = {}
	a = np.bincount(eventid.astype('int'))
	evtCount = a[a.nonzero()]
	evt_topology_dict = dict(zip(set_events, evtCount))	
else:
	from collections import Counter
	evt_topology_dict = Counter(eventid)
	evtCount = sorted(evt_topology_dict.values())


# Define figure 0 (histogram of event multiplicity)
# fig0 = plt.figure()
# bin_histogram = np.arange(0.5, np.max(evtCount) + 1.5, 1)
# evtHist, loc = np.histogram(evtCount, bins=bin_histogram, normed=True)
# plt.hist(evtCount, bins=bin_histogram, normed=True)
# plt.xlabel("Event multiplicity")
# plt.ylabel("Fraction of events")
# plt.xlim(0,20)
# plt.savefig("event_multiplicity_histogram.pdf")
# print "Events for multiplicity: ", np.array((evtHist*N_detected), dtype=int)
# print "Fraction of events for multiplicity: ", evtHist

# Define figure 1 (spectra)
# fig1 = plt.figure()
# prop = fm.FontProperties(size=10)
# # Plot original data
# binsize = 10.
# upper_range = 10000 + binsize
# binning = np.arange(1,upper_range+binsize,binsize)
# y, bins = np.histogram(endep, bins=binning, range=(1, upper_range))
# x = binning[:-1] + binsize/2.
# erry = np.sqrt(y)
# plt.loglog(x, y, drawstyle='steps-mid', color='black', label="Original data")
# plt.errorbar(x, y, yerr=erry, drawstyle='steps-mid', capsize=0, color='black')
# plt.xlim(2, upper_range)
# plt.xlabel("Energy (keV)")
# plt.ylabel("Counts keV$^{-1}$")


# Calculate original event data in 2-30 and 2-50 keV
original_2_30 = [e for e in endep if 2. <= e <= 30.]
original_2_50 = [e for e in endep if 2. <= e <= 50.]
original_2_80 = [e for e in endep if 2. <= e <= 80.]
print "Original data:", len(endep)
print "Original data 2-30 keV:", len(original_2_30)
print "Original data 2-50 keV:", len(original_2_50)
print "Original data 2-80 keV:", len(original_2_80)

		

# Single events
# Array with energy deposits for single events

# Array with (sorted) eventIDs for 1-pixel events
singles = sorted(find_key(evt_topology_dict, 1))
# Search for single events in the energy deposit array
for i in range(N_detected):
	id_evt  	= eventid[i]
	energy_evt  = endep[i]
	theta_evt 	= theta[i]
	phi_evt   	= phi[i]	
	# if i % 10000 == 0:
	# 	print "%d of %d (%.2f per cent complete)" % (i, N_detected, (i*100/float(N_detected)))
	if evt_topology_dict[eventid[i]] == 1:
		endep_s.append(energy_evt)
		endep_out.append(energy_evt)
		eventid_out.append(id_evt)
		theta_out.append(theta_evt)
		phi_out.append(phi_evt)    

# Plot single events spectrum
# y_s, bins_s = np.histogram(endep_s, bins=binning, range=(1, upper_range))
# erry_s = np.sqrt(y_s)
# plt.loglog(x, y_s, drawstyle='steps-mid', color='blue', label="Singles")
# plt.errorbar(x, y_s, yerr=erry_s, drawstyle='steps-mid', capsize=0, color='blue')

# Calculate single event data in 2-30 and 2-50 keV
single_2_30 = [e for e in endep_s if 2. <= e <= 30.]
single_2_50 = [e for e in endep_s if 2. <= e <= 50.]
single_2_80 = [e for e in endep_s if 2. <= e <= 80.]
print "Single event data:", len(endep_s)
print "Single event data 2-30 keV:", len(single_2_30)
print "Single event data 2-50 keV:", len(single_2_50)
print "Single event data 2-80 keV:", len(single_2_80)





# Search for adjacent double events and accumulation of their energy deposits, 
# for all multiple events
# ANODE MULTIPLICITY REJECTION FILTER (AMRF)
# Version 1.0
i = 0
while True:
	if i >= N_detected:
		break # end of loop 
	if i % 10000 == 0: 
		print "%d of %d (%.1f per cent complete)" % (i, N_detected, (i*100/float(N_detected)))
		
	# New eventID, determine its multiplicity
	multiplicity = evt_topology_dict[eventid[i]]
	id_evt  	 = eventid[i]
	theta_evt 	 = theta[i]
	phi_evt   	 = phi[i]	
	
	# If non-single event
	if multiplicity >= 2:
		# subarrays with X, Y and energy
		xevt = X_ID[i:(i+multiplicity)]
		yevt = Y_ID[i:(i+multiplicity)]
		eevt = endep[i:(i+multiplicity)]
		# print i, multiplicity, xevt, yevt, eevt
		# Initialize flag for all the pixels in this multiple event
		flag = [0]*multiplicity
		for j in range(multiplicity):
			# Start from the j-th event, if not already checked
			if flag[j] == 0:
				# Flag this event as checked
				flag[j] = 1
				# Initialize arrays of distances
				DX = np.fabs(xevt-xevt[j])
				DY = np.fabs(yevt-yevt[j])
				# print xevt[j], DX, yevt[j], DY
				# Find same-column pixel indices
				column_idx = np.where(DY == 0)[0]
				# Loop on these
				for k in column_idx:	
					# Loop on all other events (provided j!=k) in the same column
					if (DX[k] == 1) and (j != k):
						# Found a double event with adjacent pixels!
						en = eevt[j] + eevt[k]
						# Check if it's a unique adjacent-pixels event in this column
						if len(DX[column_idx] == 2):	
							endep_m.append(en)
							eventid_out.append(id_evt)
							endep_out.append(en)
							theta_out.append(theta_evt)
							phi_out.append(phi_evt)    
						flag[k] = 1
			
	# Jump to next event		
	i += multiplicity


# Plot multiple events spectrum (with correction, i.e. accumulation of adjacent pixels)
# y_m, bins_m = np.histogram(endep_m, bins=binning, range=(1, upper_range))
# erry_m = np.sqrt(y_m)
# plt.loglog(x, y_m, drawstyle='steps-mid', color='magenta', label='Multiple evt. corrected')
# plt.errorbar(x, y_m, yerr=erry_m, drawstyle='steps-mid', capsize=0, color='magenta')


# Calculate multiple event data in 2-30 and 2-50 keV
multiple_2_30 = [e for e in endep_m if 2. <= e <= 30.]
multiple_2_50 = [e for e in endep_m if 2. <= e <= 50.]
multiple_2_80 = [e for e in endep_m if 2. <= e <= 80.]
print "Multiple event data:", len(endep_m)
print "Multiple event data 2-30 keV:", len(multiple_2_30)
print "Multiple event data 2-50 keV:", len(multiple_2_50)
print "Multiple event data 2-80 keV:", len(multiple_2_80)


# Write output fits
eventid_out   = np.array(eventid_out)
endep_out     = np.array(endep_out) 
theta_out     = np.array(theta_out) 
phi_out       = np.array(phi_out) 
col1 = pyfits.Column(name='EventID', format='1K', array=eventid_out)
col2 = pyfits.Column(name='En_dep', format='1D', array=endep_out)
col3 = pyfits.Column(name='Theta_Primary', format='1D', array=theta_out)
col4 = pyfits.Column(name='Phi_Primary', format='1D', array=phi_out)
cols = pyfits.ColDefs([col1, col2, col3, col4])
tbhdu = pyfits.new_table(cols, header=hdr)
tbhdu.writeto(fileout, clobber=True)
hdulist.close()


# Plot new total spectrum
# y_tot_after = y_s + y_m
# erry_tot_after = np.sqrt(erry_s**2 + erry_m**2)
# plt.loglog(x, y_tot_after, drawstyle='steps-mid', color='green', label="After correction")
# plt.errorbar(x, y_tot_after, yerr=erry_tot_after, drawstyle='steps-mid', capsize=0, color='green')
# plt.legend(loc='lower left', prop=prop)
# fileimg = filein.split("fits")[0] + "pdf"
# plt.savefig(fileimg)

# Write output spectrum
# Not-normalized
binning_1 = np.arange(1.,1002., newbinsize)
x_1 = binning_1[:-1] + newbinsize/2.
y_s_1, bins_s_1 = np.histogram(endep_s, bins=binning_1, range=(1, 1001))
erry_s_1 = np.sqrt(y_s_1)
y_m_1, bins_m_1 = np.histogram(endep_m, bins=binning_1, range=(1, 1001))
erry_m_1 = np.sqrt(y_m_1)
y_1_tot_after    = y_s_1 + y_m_1
erry_1_tot_after = np.sqrt(erry_s_1**2 + erry_m_1**2)
# fileoutsp = "spectrum_notnormalized_" + filename + ".dat"
# np.savetxt(fileoutsp, zip(x_1, y_1_tot_after, erry_1_tot_after), fmt="%.4e %.4e %.4e")

# Load normalizations dictionary
filenorm = "./normalizations.txt"
f = open(filenorm)
norm_dict = {}
for line in f.readlines():
    filemac, norm = line.split()
    norm_dict[os.path.splitext(filemac)[0]] = float(norm)

# Load normalization
filenameroot = filename.split("_")[0]
print filenameroot
phi = norm_dict[filenameroot + "_v2"]
print "Normalization of input", filenameroot, phi, "particles/cm^2/s/sr"

sphereRadius = 5000     # cm
thetaMax     = 6.0      # deg
detArea      = 29400.   # cm2

tau = N_primaries / (phi * 4*np.pi**2 * sphereRadius**2 * (np.sin(np.radians(thetaMax)))**2)

print "Simulation time", tau, "s"

ynorm = y_1_tot_after/(tau*detArea*newbinsize)
errynorm = erry_1_tot_after/(tau*detArea*newbinsize)

fileoutspnorm = "spectrum_" + filename + ".dat"

np.savetxt(fileoutspnorm, zip(x_1, ynorm, errynorm), fmt="%.4e %.4e %.4e")

# figsp = plt.figure()
# plt.loglog(x, ynorm, drawstyle='steps-mid', color='black')
# plt.errorbar(x, ynorm, yerr=errynorm, drawstyle='steps-mid', capsize=0, color='black')
# plt.xlim(2,60)
# plt.xlabel("Energy (keV)")
# plt.ylabel("Counts cm$^{-2}$ s$^{-1}$ keV$^{-1}$")

# plt.show()
