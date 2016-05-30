Shadowsocks-Qt5
===============

Please check [project's wiki](https://github.com/shadowsocks/shadowsocks-qt5/wiki) for "how-tos".

Introduction
------------

Shadowsocks-Qt5 is a native and cross-platform [shadowsocks](http://shadowsocks.org) GUI client with advanced features.

Features
--------

- Shadowsocks-Qt5 is written in C++ with Qt 5.
- Support traffic statistics
- Support server latency (lag) test
- Use multiple profiles simultaneously
- `config.ini` is located under `~/.config/shadowsocks-qt5/` on \*nix platforms, or under the application's directory on Windows.

Note
----

If `ss-qt5` crashes and the **only one instance** mode is checked,
you may need to manually delete `/tmp/qipc_sharedmemory_ShadowsocksQt*`
and `/tmp/qipc_systemsem_ShadowsocksQt*`.
Otherwise, `ss-qt5` will complain that another instance is already running.
Run `ss-qt5` again is also expected to work.

LICENSE
-------

![](http://www.gnu.org/graphics/lgplv3-147x51.png)

Copyright © 2014-2016 Symeon Huang

This project is licensed under version 3 of the GNU Lesser General Public License.
