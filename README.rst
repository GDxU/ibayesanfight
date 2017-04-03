iBaye - 步步高三国霸业 for iOS
===============================

交流QQ群：526266208

贴吧讨论与反馈:
`<http://tieba.baidu.com/p/3977138152>`_

开发环境配置
''''''''''''

1. 安装emscripten
    Ubuntu::

    sudo apt install emscripten

或参考::
    http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html#platform-notes-installation-instructions-portable-sdk


2. 下载源码，编译::

    git clone --recursive https://git.oschina.net/bgwp/iBaye.git
    cd iBaye/js
    emconfigure cmake ../src
    make

