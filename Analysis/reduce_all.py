import os
import glob

sims = ['leakageCXB', 'albedo', 'neutronAlbedo', \
        'primaryAlpha', 'primaryProtons','primaryElectrons', \
        'primaryPositrons', 'secondaryProtons', 'secondaryPositrons', 'secondaryElectrons']
nprim = ['1e8', '1e8', '1e8', \
        '1e6', '1e6', '1e6', '1e6', \
        '1e6', '1e6', '1e6']

dictionary = dict(zip(sims, nprim))        

# for filein in glob.glob("*.tar.gz"):
#     os.system("tar xzvf " + filein)

for sim in sims:
    n = dictionary[sim]
    os.system("python mergeRoot.py %s_%s scorefile_%s" % (sim, n, sim))
    os.system("python convertRoot2Fits.py %s_%s.root" % (sim, n))
    

for filein in glob.glob("*.fits.gz"):
    print filein
    os.system("python multiplicity_v6.py %s" % filein)