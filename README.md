# promptline-cpp

A minimalist implementation of a powerline style prompt in modern C++.

## Samples

powerline-esque:
![powerline colors](images/powerline-colors.png "powerline colors")

gruvbox-esque:
![gruvbox colors](images/gruvbox-colors.png "gruvbox colors")
![gruvbox with ssh segment](images/gruvbox-with-ssh.png "gruvbox with ssh segment")

## How to use

Currently supports zsh and bash.

Uses ANSI escape sequences.

Build with CMake. Then `sudo make install`.

### zsh

Add the following to your .zshrc and replace [path/to/promptline-cpp/executable] with the corresponding path.
If a prompt on the right-hand side is not desired, simply leave out the
RPS1 line.
```zsh
function promptline_precmd() {
    PS1=$([path/to/promptline-cpp/executable] "$?")
    RPS1=$([path/to/promptline-cpp/executable] "$?" --right)
}

function install_promptline_precmd() {
  for s in "${precmd_functions[@]}"; do
    if [ "$s" = "promptline_precmd" ]; then
      return
    fi
  done
  precmd_functions+=(promptline_precmd)
}

if [ -f [path/to/promptline-cpp/executable] ]; then
    install_promptline_precmd
fi
```

### bash

Add the following to your .bashrc and replace [path/to/promptline-cpp/executable] with the corresponding path
```bash
function _update_prompt() {
    PS1="$([path/to/promptline-cpp/executable] "$?")"
}

if [ -f "[path/to/promptline-cpp/executable]" ]; then
    PROMPT_COMMAND="_update_prompt; $PROMPT_COMMAND"
fi
```

## Customization

By default the prompt uses only ANSI color codes `000` through `015`. If the
terminal emulator remaps these color codes via e.g. a colorscheme, this will be
taken into account.

For each segment, the foreground and background color may be specified in a .toml
file. This file should be placed in $HOME/.config/promptline-cpp/colors.toml. As
a reference, checkout the .toml files in the colors directory.

If a segment is not specified, it's default foreground and background color
will be used. If no config file is found, all segments will have their default colors.

To configure the order of the segments and on which side they  should be
displayed, create a file named *segments.toml*. There the segments and their
priority can be specified as follows:

```toml
[left]
user = 10
git = 20

[right]
cwd = 10
time = 20
```

For the default configuration, refer to the file *default_segments.toml* in the
[config samples](config_samples). If there is no segments.toml file the default
configuration will be used.
