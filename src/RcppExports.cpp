#include <R.h>
#include <Rcpp.h>
#include <Rinternals.h>
#include <fstream>
#include <iostream>
#include "recordio.h"

namespace grail {
namespace {
struct Info {
  std::string path;
  std::ifstream in;
  std::unique_ptr<RecordIOReader> r;
  const char* xxx;
};

}  // namespace

RcppExport SEXP recordio_newreader(SEXP path_sexp) {
  const auto path =
      std::string(Rcpp::traits::input_parameter<std::string>::type(path_sexp));

  Rcpp::XPtr<Info> r(new Info{
      path, std::ifstream(path), nullptr, "foobar",
  });
  if (r->in.fail()) {
    ::Rf_error("open %s: %s", path.c_str(), strerror(errno));
    return R_NilValue;
  }

  r->r = std::move(NewRecordIOReader(&r->in));
  std::cout << "PATHpath:" << std::string(path) << "\n";
  return r;
}

RcppExport SEXP recordio_close(SEXP r_sexp) {
  Rcpp::XPtr<Info> r(r_sexp);
  std::string err = r->r->Error();
  r->r.reset();
  r->in.close();
  if (err != "") {
    ::Rf_error("close %s: %s", r->path.c_str(), err.c_str());
  }
  return R_NilValue;
}

RcppExport SEXP recordio_next(SEXP r_sexp) {
  Rcpp::XPtr<Info> r(r_sexp);
  if (!r->r->Scan()) {
    if (r->r->Error() != "") {
      ::Rf_error("next %s: %s", r->path.c_str(), r->r->Error().c_str());
    }
  }
  const auto& src = *r->r->Mutable();
  Rcpp::RawVector v(src.size());
  int i = 0;
  for (char ch : src) {
    v[i] = ch;
    i++;
  }
  return v;
}

}  // namespace grail
