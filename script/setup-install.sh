## A script to set up the environment to install, build and run the e1039-core
## package.  Usage:
##   source /path/to/setup-install.sh /path/to/your_inst_directory
##
## This script first creates an installation directory together with a 
## script "this-core.sh".  It then tries to find proper E1039_RESOURCE and 
## E1039_SHARE directories depending on the host name.  When successful, 
## it creates a script "this-e1039.sh", which sets up all the resource,
## share and core environments at once.
##
## One need not use this script but can set up everything by oneself.  But 
## this script should be helpful in preparing for an easily-reproducible 
## environment.  Any questions/requests can be sent to Kenichi.
DIR_SCRIPT=$(dirname $(readlink -f $BASH_SOURCE))

if [ -z "$1" ] ; then
    echo "The 1st argument must be an installation directory,"
    echo "or 'auto' to auto-select it."
    echo "Abort."
    return
elif [ "X$1" = 'Xauto' ] ; then
    DIR_INST=$(readlink -f $DIR_SCRIPT/../../e1039-core-inst)
else
    DIR_INST=$(readlink -m "$1")
fi
echo "Use this installation directory:"
echo "  $DIR_INST"

##
## Create the setup script
##
mkdir -p $DIR_INST
\cp $DIR_SCRIPT/this-core-org.sh $DIR_INST/this-core.sh

##
## Check and set up the parent environments.
##
E1039_ROOT=
if   [ ${HOSTNAME:0:11} = 'seaquestdaq' -o \
       ${HOSTNAME:0:12} = 'spinquestana' ] ; then
    echo "Use the environment for seaquestdaq/spinquestana."
    E1039_ROOT=/data2/e1039
elif [ ${HOSTNAME:0:12} = 'seaquestgpvm' -o \
       ${HOSTNAME:0:13} = 'spinquestgpvm' ] ; then
    echo "Use the environment for seaquestgpvm/spinquestgpvm."
    E1039_ROOT=/e906/app/software/osg/software/e1039
fi
if [ -z "$E1039_ROOT" ] ; then
    echo "Your host is not supported by this script."
    echo "You can ask the manager (Kenichi) how to proceed, or"
    echo "try to set E1039_RESOURCE and E1039_SHARE properly by yourself."
    return
fi
{
    echo "source $E1039_ROOT/resource/this-resource.sh"
    echo "source $E1039_ROOT/share/this-share.sh"
    echo "source $DIR_INST/this-core.sh"
} >$DIR_INST/this-e1039.sh

##
## Message
##
echo
echo "A setup script was created;"
echo "  $DIR_INST/this-e1039.sh"
echo "You should source it when you start building or executing this e1039-core "
echo "package.  Next you likely source the script, move to a build directory "
echo "and execute 'build.sh'."
