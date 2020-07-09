# Build dev packages from source and install to a "TOP" directory
export TOP=$(pwd)
export PATH=$PATH:$TOP/bin
export LD_LIBRARY_PATH=$TOP/lib

# Just for cogs we need ERS and ERS needs BOOST
source /cvmfs/dune.opensciencegrid.org/dunedaq/DUNE/products/setup
setup ers v0_26_00 -q e19:prof
setup boost v1_70_0 -q e19:prof

# # For cogs demo we need cmake to build Avro CPP:
# setup cmake v3_17_2

# For moo we need a supported Python version, take from larsoft
PRODUCTS=$PRODUCTS:/cvmfs/larsoft.opensciencegrid.org/products
setup python v3_7_2


# See guide on how this gets created and populated
if [ -d "$TOP/venv" ] ; then
    source $TOP/venv/bin/activate
else
    echo "moo not yet installed: $TOP/venv"
fi
