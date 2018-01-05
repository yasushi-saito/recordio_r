# rm -f *.o *.so
cd src
echo make: Entering directory \'$(pwd)\'
export PKG_CXXFLAGS=$(Rscript -e "Rcpp:::CxxFlags()")
R CMD SHLIB *.cc
