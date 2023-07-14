class TermNotes < Formula
  desc "Terminal-based note-taking application"
  homepage "https://github.com/felipealfonsog/TermNotes"
  url "https://github.com/felipealfonsog/TermNotes/archive/refs/tags/v.1.0.1.tar.gz"
  sha256 "43db1b333d8902b15df4444d12e76c6d80fa9535cb377f7594d3cfa19c64e869"
  license "MIT"
  depends_on "gcc" => :build
  depends_on "vim"
  depends_on "nano"

  def install
    system "./setup"
    bin.install "term_notes"
  end

  test do
    # Add some test cases here
  end
end
