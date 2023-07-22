
# Term Notes

"TermNotes" is a command-line note management utility designed to help you organize your ideas and reminders efficiently. It allows you to create, display, update, and delete notes directly from the terminal, providing you with a fast and straightforward workflow. With "TermNotes," you can keep track of your thoughts and important tasks, all within your favorite command-line environment. Simplify your life and enhance your productivity with this minimalist yet powerful tool.

![Version](https://img.shields.io/github/release/felipealfonsog/TermNotes.svg?style=flat&color=blue)
![Main Language](https://img.shields.io/github/languages/top/felipealfonsog/TermNotes.svg?style=flat&color=blue)
[![Open Source? Yes!](https://badgen.net/badge/Open%20Source%20%3F/Yes%21/blue?icon=github)](https://github.com/Naereen/badges/)

[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![GPL license](https://img.shields.io/badge/License-GPL-blue.svg)](http://perso.crans.org/besson/LICENSE.html)


[![Vim](https://img.shields.io/badge/--019733?logo=vim)](https://www.vim.org/)
[![Visual Studio Code](https://img.shields.io/badge/--007ACC?logo=visual%20studio%20code&logoColor=ffffff)](https://code.visualstudio.com/)

![Screenshot of the Term Notes application interface](imgs/sshot_termnotes.jpg)

## Term-Notes Installer 🚀

[![Installer Success](https://img.shields.io/badge/Installer-Success-orange)](https://github.com/felipealfonsog/TermNotes)

Hey there! 👋 I'm excited to share that I successfully created a convenient Bash installer for Term-Notes, a terminal-based note-taking application.

📝 With this installer, you can effortlessly install Term-Notes on your Mac OS or Linux system by executing a simple script. No more hassles with manual compilation or dependencies!

🚀 The installer takes care of everything: downloading the source code, compiling the program, and even checking for Homebrew or Linux package managers to ensure smooth installation.

💻 Whether you're on Mac OS or Linux, the installer streamlines the process, so you can focus on taking notes without any hassle.

By the way, we had some hurdles along the way. Homebrew didn't accept our project, but screw it! 😄 We persevered and made it happen, developing an easy-to-use installer with some cool ASCII ART!

#### To Install it: 
To install Term-Notes, simply run the installer script available [here](https://github.com/felipealfonsog/TermNotes/blob/main/installer.sh).

Or just Copy - Paste in your terminal and use wget to start downloading the installer:

   ```
   wget https://github.com/felipealfonsog/TermNotes/blob/main/installer.sh
   ```

   On macOS to download - wget - just install it with Homebrew:

   ```
   brew install wget
   ```

#### Important note when installing:

If you encounter issues executing the file in the terminal, follow these simple steps to fix it:

1. Open your terminal.
2. Navigate to the directory where the installer script is located using the `cd` command.
3. Run the following command to grant execute permission to the installer script:

   ```
   chmod +x installer.sh
   ```
   
4. Now you can run the installer without any problems.

   ```
   ./installer.sh
   ```

Now type 'term-notes' in the terminal and enjoy using Term-Notes! 😊🚀

Feel free to reach out if you need any further assistance!


Please note that if you encounter any issues or have suggestions, feel free to raise an issue on the [TermNotes repository](https://github.com/felipealfonsog/TermNotes/issues). Your feedback is invaluable!

🌈 Thank you for joining me on this journey, and I hope Term-Notes brings value to your workflow. Let's continue making technology accessible and enjoyable for everyone! 🤖💙


## Installation
### Via AUR using YAY

[![AUR](https://img.shields.io/aur/version/term-notes.svg)](https://aur.archlinux.org/packages/term-notes)

https://aur.archlinux.org/packages/term-notes

Term Notes is available on AUR (Arch User Repository), and it can be installed using the `yay` package manager. Follow the steps below to install Term Notes:

1. Make sure you have `yay` installed. If not, you can install it with the following command:
   
   ```
   sudo pacman -S yay
   ```
   Once yay is installed, you can install Term Notes by running the following command:
   
   ```
   yay -S term-notes
   ```
This command will automatically fetch the package from AUR and handle the installation process for you.

#### Project Availability Update: Homebrew Rejection

[![Homebrew Rejected](https://img.shields.io/badge/Homebrew-Not%20Accepted-yellow)](https://github.com/TermNotes)

I regret to inform you that the project, Term Notes, has been rejected by Homebrew for publication in their package repository. This means that Linux users from different distros, unfortunately, won't be able to install Term Notes directly through Homebrew. However, we have an alternative solution for Arch Linux users!

Term Notes can still be installed through the YAY package manager, ensuring Arch Linux users can enjoy the benefits of the note-taking application. Simply follow the instructions provided in the project's documentation to install Term Notes using YAY.

For users on other Linux distributions and macOS, don't worry! You can still compile and use the binary file from the cloned GitHub project repository. Although it won't be installed system-wide, you can run the application directly from the project folder. I apologize for any inconvenience this may cause.

#### Prerequisites

- GCC (GNU Compiler Collection)
- Nano or Vim text editor

#### Compiling the Source Code

1. Clone the repository:

```
git clone https://github.com/felipealfonsog/TermNotes.git
```
3. Navigate to the project directory:

```
cd TermNotes/src
```
4. Compile the source code:

```
gcc -o term-notes term_notes.c
```

#### Usage

- To create a new note:
term_notes create

- To edit an existing note:
term_notes edit [note_id]

- To view all notes:
term_notes list

- To delete a note:
term_notes delete [note_id]


#### Contributing

Contributions are welcome! Here's how you can contribute to Term Notes:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature-name`.
3. Make your changes and commit them: `git commit -m 'Add your feature'`.
4. Push the changes to your branch: `git push origin feature/your-feature-name`.
5. Create a new pull request.

#### License

Term Notes is licensed under the MIT License. See [LICENSE](LICENSE) for more information.

#### Contact

Hello! My name is Felipe, and I'm a passionate Computer Science Engineer. I'm also the creator of this project. If you have any questions, suggestions, or just want to chat, feel free to reach out to me. I'd be more than happy to help!

- Email: f.alfonso@res-ear.ch
- LinkedIn: [felipealfonsog](https://www.linkedin.com/in/felipealfonsog/)
- GitHub: [felipealfonsog](https://github.com/felipealfonsog)

#### Support and Contributions

If you find this project helpful and would like to support its development, there are several ways you can contribute:

- **Code Contributions**: If you're a developer, you can contribute by submitting pull requests with bug fixes, new features, or improvements. Feel free to fork the project and create your own branch to work on.
- **Bug Reports and Feedback**: If you encounter any issues or have suggestions for improvement, please open an issue on the project's GitHub repository. Your feedback is valuable in making the project better.
- **Documentation**: Improving the documentation is always appreciated. If you find any gaps or have suggestions to enhance the project's documentation, please let me know.

[![Buy Me a Coffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-%E2%98%95-FFDD00?style=flat-square&logo=buy-me-a-coffee&logoColor=black)](https://www.buymeacoffee.com/felipealfonsog)
[![PayPal](https://img.shields.io/badge/Donate%20with-PayPal-00457C?style=flat-square&logo=paypal&logoColor=white)](https://www.paypal.com/felipealfonsog)
[![GitHub Sponsors](https://img.shields.io/badge/Sponsor%20me%20on-GitHub-%23EA4AAA?style=flat-square&logo=github-sponsors&logoColor=white)](https://github.com/sponsors/felipealfonsog)

Your support and contributions are greatly appreciated! Thank you for your help in making this project better.

