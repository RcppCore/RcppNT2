NT2_URL <- "https://github.com/jfalcou/nt2"
COMMIT  <- "f19e80f55cad6db21ccb3c7f216efecf45c91250"

# Helpers
pathProg <- function(name) {
  prog <- Sys.which(name)
  if (!nzchar(prog))
    stop("No program named '", name, "' on the PATH!", call. = FALSE)
  prog
}

cmakeDef <- function(name, value) {
  sprintf("-D%s=%s", name, value)
}

cmake <- pathProg("cmake")
make <- pathProg("make")
git <- pathProg("git")
patch <- pathProg("patch")

# End helpers

# Find the root directory
owd <- getwd()
if (!grepl("RcppNT2", owd))
  stop("this script should be called from within the RcppNT2 sources directory")
dir <- gsub("RcppNT2.*", "RcppNT2", owd)
setwd(dir)

# Check out the 'nt2' sources
if (!dir.exists("nt2"))
  system2(git, c("clone", NT2_URL))
setwd("nt2")

# Check out the relevant commit
system2(git, c("checkout", COMMIT))

# Prepare installation directory
if (dir.exists("install"))
  unlink("install", recursive = TRUE)
dir.create("install")
installDir <- file.path(getwd(), "install")

# Enter 'nt2' directory, and check out relevant commit
if (dir.exists("build"))
  unlink("build", recursive = TRUE)
dir.create("build")
setwd("build")

# Call cmake to prepare the build
system2(cmake, c(
  "..",
  cmakeDef("CMAKE_INSTALL_PREFIX", installDir)
))

# Call 'make', 'make install' to build and install
system2(make)
system2(make, "install")

# Go back to parent directory
setwd(owd)

# Copy all of the relevant headers over
includePath <- file.path(installDir, "include")
from <- list.files(includePath, full.names = TRUE)
to   <- file.path("inst/include")
if (!dir.exists(to))
  dir.create(to, recursive = TRUE)
file.copy(from, to, recursive = TRUE)

# Apply all of our patches
patches <- list.files("patch", full.names = TRUE)
for (patch in patches) {
  system2(patch, c("-p1", "<", patch))
}
