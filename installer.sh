#!/bin/bash


#*************************************
# Terminal Notes Utility written in C
#*************************************
# Simple: Create and manage notes from the terminal
#*************************************
# Developed and engineered by 
# Felipe Alfonso Gonzalez <f.alfonso@res-ear.ch>
# Computer Science Engineer
# Chile
#*************************************
    

echo "

▀▀█▀▀ █▀▀ █▀▀█ █▀▄▀█ ░░ ▒█▄░▒█ █▀▀█ ▀▀█▀▀ █▀▀ █▀▀ 
░▒█░░ █▀▀ █▄▄▀ █░▀░█ ▀▀ ▒█▒█▒█ █░░█ ░░█░░ █▀▀ ▀▀█ 
░▒█░░ ▀▀▀ ▀░▀▀ ▀░░░▀ ░░ ▒█░░▀█ ▀▀▀▀ ░░▀░░ ▀▀▀ ▀▀▀


  ╔═══════════════════════════════════════╗
  ║                                       ║
  ║   ~ Term Notes ~                      ║
  ║   Developed with ❤️ by                 ║
  ║   Felipe Alfonso González L.          ║
  ║   Computer Science Engineer           ║
  ║   Chile                               ║
  ║                                       ║
  ║   Contact: f.alfonso@res-ear.ch       ║
  ║   Licensed under GNU/GPL and MIT      ║
  ║   GitHub: github.com/felipealfonsog   ║
  ║   LinkedIn:                           ║
  ║   linkedin.com/in/felipealfonsog      ║
  ║                                       ║
  ╚═══════════════════════════════════════╝


"


echo "Welcome to the Term-Notes installer! v.1.0.1"
echo "*************************************************

"

if [[ ! -x "$0" ]]; then
    echo "The installer script does not have execute permission. Do you want to grant it?"
    select yn in "Yes" "No"; do
        case $yn in
            Yes)
                chmod +x "$0"
                exec "$0" "$@"
                ;;
            No)
                echo "Exiting program."
                exit 0
                ;;
            *)
                echo "Invalid option. Please choose a valid option."
                ;;
        esac
    done
fi


if [[ $(uname) == "Darwin" ]]; then
    if ! command -v brew &> /dev/null; then
        echo "Homebrew is not installed on macOS. Do you want to install it?"
        select yn in "Yes" "No"; do
            case $yn in
                Yes)
                    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
                    break
                    ;;
                No)
                    echo "Exiting program."
                    exit 0
                    ;;
                *)
                    echo "Invalid option. Please choose a valid option."
                    ;;
            esac
        done
    fi
elif [[ $(uname) == "Linux" ]]; then
    if ! command -v brew &> /dev/null; then
        echo "Homebrew/Linuxbrew is not installed on Linux. Do you want to install it?"
        select yn in "Yes" "No"; do
            case $yn in
                Yes)
                    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
                    break
                    ;;
                No)
                    echo "Exiting program."
                    exit 0
                    ;;
                *)
                    echo "Invalid option. Please choose a valid option."
                    ;;
            esac
        done
    fi


    if ! command -v gcc &> /dev/null; then
        echo "GCC is not installed on Linux. Do you want to install it?"
        select yn in "Yes, using Homebrew" "Yes, using package manager" "No"; do
            case $yn in
                "Yes, using Homebrew")
                    brew install gcc
                    break
                    ;;
                "Yes, using package manager")
                    if [[ -f /etc/arch-release ]]; then
                        sudo pacman -S gcc
                    elif [[ -f /etc/debian_version ]]; then
                        sudo apt-get update && sudo apt-get install gcc
                    else
                        echo "Unsupported Linux distribution. Please install GCC manually, read documentation according to your distro, and re-run the installer."
                        exit 1
                    fi
                    break
                    ;;
                "No")
                    echo "Exiting program."
                    exit 0
                    ;;
                *)
                    echo "Invalid option. Please choose a valid option."
                    ;;
            esac
        done
    fi
fi


curl -o term_notes.c https://github.com/felipealfonsog/TermNotes/raw/main/src/term_notes.c

# Compile the program and rename it to term-notes
gcc -o term-notes term_notes.c

# Move the executable to the appropriate location
if [[ $(uname) == "Darwin" ]]; then
    sudo mv term-notes /usr/local/bin/
else
    if [[ -f /etc/arch-release ]]; then
        sudo mv term-notes /usr/bin/
    elif [[ -f /etc/debian_version ]]; then
        sudo mv term-notes /usr/local/bin/
    else
        sudo mv term-notes /usr/local/bin/
    fi
fi


chmod +x /usr/local/bin/term-notes


rm -P term_notes.c

echo "-------------------------------------------------------------------"

if [[ $(uname) == "Darwin" ]]; then
    echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bash_profile
    source ~/.bash_profile
    echo "Installation has been completed."
else
    if [[ -f ~/.bashrc ]]; then
        echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bashrc
        source ~/.bashrc
    elif [[ -f ~/.bash_profile ]]; then
        echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bash_profile
        source ~/.bash_profile
    else
        echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.profile
        source ~/.profile
    fi
    echo "Installation has been completed."
fi


reload_shell() {
    if [[ $(uname) == "Darwin" ]]; then
        source ~/.bash_profile
    elif [[ $(uname) == "Linux" ]]; then
        if [[ -f /etc/arch-release ]]; then
            source ~/.bashrc
        elif [[ -f /etc/debian_version ]]; then
            source ~/.bashrc
        else
            source ~/.bashrc
        fi
    fi
}


reload_shell

echo "-------------------------------------------------------------------"
echo "You can now run the program by typing 'term-notes' in the terminal."
echo "-------------------------------------------------------------------"
