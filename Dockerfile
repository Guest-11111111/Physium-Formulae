FROM ghcr.io/therainbowphoenix/cp-codespace:beta-02

USER root

RUN apt-get update && apt-get install -y nano vim clangd-13 clang-format-13 wget

USER dev

RUN mkdir ~/tmp
RUN wget https://raw.githubusercontent.com/ClasspadDev/faq/main/faq.md -O faq

RUN echo -e "echo \"$(tput setaf 2)\n\n      Welcome to the ClassPad SDK ! \n                You can build using \"make bin\"\n                \"make\" and compiling should begin \n                Check the faq \"cat ~/faq\n"\n\n$(tput sgr0)\"" >> ~/.bashrc\n
