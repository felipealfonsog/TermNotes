class TermNotes < Formula
  desc "Terminal-based note-taking application"
  homepage "https://github.com/felipealfonsog/TermNotes"
  url "https://github.com/felipealfonsog/TermNotes/archive/refs/tags/v.1.0.2.tar.gz"
  sha256 "43db1b333d8902b15df4444d12e76c6d80fa9535cb377f7594d3cfa19c64e869"
  license "MIT"

  depends_on "gcc"
  depends_on "vim"
  depends_on "nano"

  def install
    if OS.mac?
      bin.install "term_notes" => "term-notes"
    else
      bin.install "term_notes"
    end
  end

  def caveats
    <<~EOS
      'Term Notes' has been installed!

      On Mac OS, you can run the program using 'term-notes'.

      On Linux, you may need to create a symbolic link to make it accessible globally.
      Run the following command:

        sudo ln -s #{opt_bin}/term_notes /usr/local/bin/term-notes

      Enjoy taking notes with 'Term Notes'!
    EOS
  end

  test do
    # Add your test logic here
  end
end
