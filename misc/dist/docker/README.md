## A Docker image to build Linux, Windows and Android active binaries.

The main reason to write this, is to provide a simple way in all platforms to integrate external active modules and build a custom version of active.

## usage
1. Install docker on Linux or docker toolbox on Windows or Mac.
2. Open a terminal on linux or "Docker Quickstart Terminal" on Windows or Mac.
3. Run command:
	- Linux: `cd`
	- Windows: `cd /c/Users/YOUR_USERNAME`
	- Mac: `cd /Users/YOUR_USERNAME`
4. Get active source code: `git clone https://github.com/activeengine/active.git`
5. Run command: `cd active/tools/docker`
6. Run command: `docker build -t active .`(In Linux run Docker commands with `sudo` or add your user to docker group before run the Docker commands). The active docker image will be build after a while.
7. Run command:
	- Linux: `docker run -it --name=active-dev -v /home/YOUR_USERNAME/active:/active-dev/active active`
	- Windows: `docker run -it --name=active-dev -v /c/Users/YOUR_USERNAME/active:/active-dev/active active`
	- Mac: `docker run -it --name=active-dev -v /Users/YOUR_USERNAME/active:/active-dev/active active`
	You are in the active-dev container and /active-dev directory now.
8. Run `./install-android-tools` to download and install all android development tools.
9. Run command: `source ~/.bashrc`
10. Run command: `cd active`
11. Run command: `scons p=android target=release` to test everything is ok. You can set platform to x11, windows, android, haiku and server.

After use and exit, you can use this environment again by open terminal and type commands: `docker start active-dev && docker attach active-dev`.

### Windows and Mac stuffs:

- Speed up compilation:
	- Exit from container.
	- Run command: `docker-machine stop`
	- Open "Oracle VM VirtualBox".
	- In settings of default VM increase CPU cores and RAM to suitable values.
	- Run command: `docker-machine start`
	- Run command: `docker start active-dev && docker attach active-dev`

- ssh to VM(can be useful sometimes):
	- `docker-machine ssh`

Check docker and boot2docker projects for more details.
