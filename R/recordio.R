#' Create a recordio reader.
#'
#' @export
#' @param path path to recordio file.
#' @return a reader object
#'
#' @examples
#' f <- recordio_newreader("/tmp/test.recordio")
#' data <- recordio_next(f)
#' recordio_close(f)
recordio_newreader <- function(path) {
       .Call("recordio_newreader", path)
}

#' Close a recordio reader.
#'
#' @export
#' @param r reader object created by recordio_newreader.
#' @return nil
recordio_close <- function(r) {
       .Call("recordio_close", r)
}

#' Read the next record from a recordio reader
#'
#' @export
#' @param r reader object created by recordio_newreader.
#' @return a raw byte vector, or nil in case of EOF.
recordio_next <- function(r) {
       .Call("recordio_next", r)
}
