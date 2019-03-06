// ngrs - ngr shell
// Copyright (c) 2018 Aigbe Research

use structopt::StructOpt;

#[derive(StructOpt)]
struct Cli {
    /// prompt id
    hostname: String,
    /// The path to the file to read
    #[structopt(parse(from_os_str))]
    path: std::path::PathBuf,
}