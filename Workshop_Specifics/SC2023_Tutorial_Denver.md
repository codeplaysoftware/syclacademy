
# SC23 Tutorial Resources

- SC23 Tutorial Resources
  - [Online PVC system available](#online-pvc-system-available)
    - [Get Developer Cloud Account](#get-developer-cloud-Accoun)
    - [Web browser login Developer Cloud](#web-browser-login-developer-cloud)
    - [ssh login Developer Cloud](#ssh-login-developer-cloud)
    - [Best ssh configuration](#best-ssh-configuration)
  - [Download the SYCL Book](#download-the-sycl-book)
  - [How Developer Cloud SLURM nodes are organized](#how-developer-cloud-slurm-nodes-are-organized)

- More information, for the curious
  - [SSH Setup](#ssh-setup)
    - [ssh-keygen](#ssh-keygen)
    - [SSH Public Key Creation](#ssh-public-key-creation)
    - [SSH folder and file permissions](#ssh-folder-and-file-permissions)
  - [Head Node vs Compute Nodes](#head-node-vs-compute-nodes)
    - [Head Node](#head-node)
    - [Interactive Worker Nodes](#interactive-worker-nodes)
      - [Go interactive!](#go-interactive)
  - [Environment Setup](#environment-setup)
  - [Verify it works / Troubleshoot](#verify-it-works--troubleshoot)
  - [VS Code Desktop Client](#vs-code-desktop-client)
    - [Overview of Steps](#overview-of-steps)
  - [Additional Software](#additional-software)
  - [Common Slurm Commands](#common-slurm-commands)
  - [Sample GPU Test Code](#sample-gpu-test-code)
  - [An Example Script](#an-example-script)
  - [Running MPI](#running-mpi)
  - [If you use MobaXterm](#if-you-use-mobaxterm)
  - [VTune, Advisor, PTrace - and other things you will get later](#vtune-advisor-ptrace---and-other-things-you-will-get-later)
  - [FAQs: Super Important Tips that may be non-obvious](#faqs-super-important-tips-that-may-be-non-obvious)

---
## Online PVC system available

For the tutorial, you are welcome to use any system you wish.

Intel has provide free access, for learning purposes, to using systems with Xeon processors and four PVC cards with tools preinstalled.  It is quick and easy to get going which this option for the tutorial.

--- 
## Get Developer Cloud Account

Create an account (or sign-in) at [cloud.intel.com](https://cloud.intel.com).

--- 
## Web browser login Developer Cloud

Once you are logged in, launch a Jupyter notebook by clicking the "Launch JupyterLab" in the upper right of the web page [console.cloud.intel.com/training](https://console.cloud.intel.com/training).

Once you arrive to the Jupyter portal, you can upload/download files, browse exercises, and you can opn terminals by clicking the terminal icon.

Open a terminal, and make note of your username (it is long) since you may want to know it for direct ssh access.

Note: when we use Jupyter to access the training material, we arel automatically connected to a worker node with PVCs where we can edit/compile/debug as well as run our applications.

--- 
## ssh login Developer Cloud

Although it is not advertised, you login supports ssh as well.  You'll need to know your username (which is long) from your initial login (see above).

You must upload your public key (ed25519 or RSA 4096 level of strength). If you have not done so for your cloud.intel.com account, you need to visit [console.cloud.intel.com/security/publickeys](https://console.cloud.intel.com/security/publickeys) and upload an ssh key (your PUBLIC key - must be ed25519 or RSA 4096 level of strength).

If you want information on how to create a key, please refer to [SSH Setup](#ssh-setup).

Once you have a key registered with your account, we have to do a slightly strange sequence to convince the Intel system to upload your key into the training SLURM nodes.
visit [console.cloud.intel.com click training then click any class - this link should magically do all that](https://console.cloud.intel.com/training/detail/9b8933a6-b466-4c69-8217-9a09d084a55a)

Now, select the "Options" and then click the "Launch using SSH".   This will actually pop up a window with the actual command for the next step. It also magically put your ssh key in the right place for the next step.

Finally - after you uploaded a key and did the little step above to force it to propogate to the training SLURM nodes (which we will ssh into), 
you can then login with ssh (see our next note for recommendation to improve on this).  Simply use:

```bash
ssh <your really long user name>@idcbetabatch.eglb.intel.com
```

then

```bash
srun --pty bash
source /opt/intel/oneapi/setvars.sh
```


If your ssh fails, first be sure you have an internet connection without proxies. If you are sitting behind a firewall, you will have to figure out how to set up the right proxy information with ssh.

If you ssh fails because the system is refusing to use your key, it is nearly always a permissions issue.  Please carefully follow the instruction on how to ensure permissions are correct on your local machine by reviewing [SSH folder and file permissions](#ssh-folder-and-file-permissions).

It is possible you did not upload your key correctly, or you did not trigger the magical copying by clicking "Launch using SSH" above.  Try the steps again, or grab an instructor (esp. James Reinders), or both.

Do not hestitate to ask an instructor for help!

It is *important* to understand that the initial ssh brings us to a head node where we should immdeiately us the "srun" command. Please be well versed in [How Developer Cloud SLURM nodes are organized](#nodeorganization) on the organization of the Developer Cloud SLURM setup (it's a little unusual). Always use 'srun --pty bash' as soon as you ssh to a head node.

The source command sets up the tools (preinstalled) to be on your paths and ready to use.

--- 
## Best ssh configuration
We do recommend making it easier and more reliable by adding this to your ~/.ssh/config and which allows us to simply use "ssh mydevcloud"

```bash
Host mydevcloud
Hostname idcbetabatch.eglb.intel.com
User <your really long user name>
IdentityFile ~/.ssh/yourSSHkey
ServerAliveInterval 60
ServerAliveCountMax 25
StrictHostKeyChecking no
UserKnownHostsFile=/dev/null
```

--- 
## Download the SYCL Book

The SYCL book is an excellent resources for learning more.  We highly recommend having a copy of the newly released (October 2023) 'second edition' of the book.

It is available for download from [HERE](https://rd.springer.com/book/10.1007/978-1-4842-9691-2).

It is also available as a printed edition (identical content) from book sellers [e.g., Amazon](https://www.amazon.com/Data-Parallel-Programming-Accelerated-Systems/dp/1484296907).

The second edition can easily be differentiated from the first edition because the second edition has the official SYCL logo on the cover.

![image](https://media.springernature.com/full/springer-static/cover-hires/book/978-1-4842-9691-2?as=png)


--- 
## How Developer Cloud SLURM nodes are organized

If you login via Jupyter, you will be connected to a worker node directly.

However, if you use ssh you will arrive at a head node.  Unlike most SLURM systems, we do *not* want user staying on the head node. Instead, users should immediately start an interactive session on a worker node by doing an "srun --pty bash".

This is NOT a cluster, and it is not a system that will give you root access.  The system is a shared system (please be respectful of others in not hogging resources unnecessarily), not a virtualized one.

This IS a system with round-the-clock access to systems with 4th Gen Intel® Xeon® Scalable processors and Intel GPU Max series GPUs (PVCs).


---
# More information, for the curious

The following collection of information may be useful, but is not really necessary for our tutorial.

---
## SSH Setup

This information explains step-by-step how to get a ssh key. If you already know how, you do not need to read this section. If you already have a strong enough key, you do not need to create a new one.

### ssh-keygen

ssh-keygen is a tool for creating new authentication key pairs for SSH. Such key pairs are used for automating logins, single sign-on, and for authenticating hosts.  The system uses SSH Keys exclusively and you will never use a password for authentication.

### SSH Public Key Creation

To create a key use the `ssh-keygen` utility found in your terminal application.

While using WSL, Linux, or MAC clients run this command:
```bash
ssh-keygen -o -a 100 -t ed25519 -f ~/.ssh/id_ed25519_idc -C "your@email.com"
```

Or, in Windows PowerShell run this command:
```bash
ssh-keygen -o -a 100 -t ed25519 -f C:\Users\YourID\.ssh\id_ed25519_idc
```

The passphrase is optional and you can hit enter for no pass phrase.  This will result in two files being generated: `id_ed25519_idc` and `id_ed25519_idc.pub` take care of these files as they are the private and public key pair that you will need.  Never ever share anything other than the public key (the .pub file).

### SSH folder and file permissions

Ensure that permissions are correct when on Linux or MacOS - these are the commands to force that:

```bash
chmod 700 ~/.ssh
chmod 600 ~/.ssh/config
chmod 600 ~/.ssh/known_hosts*
chmod 400 ~/.ssh/id*
chmod 400 ~/.ssh/*.pub
```

--- 
## Environment Setup

Enter `source /opt/intel/oneapi/setvars.sh` and the oneAPI development environment will be initialized.

Enter `conda env list` and activate the python environment of your choice.  Both Tensorflow and Pytorch environments have Jupyter installed.  If you don't like those environments create your own conda environment and customize to your liking. 

---
## Verify it works / Troubleshoot

Please verify that your environment works at this point enough to "see" the PVC (GPUs).  If you cannot, there is little point in doing more until we fix it so you *can* see the GPUs.

Here are the commands you should have done already to reach a node with GPUs, plus three more.  The first command is on your system. The second command is on the head node. The last three commands will be on an a node that has PVC cards.  The output of these commands see if have access to the GPU cards, and if not give us a hint on why not.

```bash
ssh myidc
srun --pty bash
groups  # Key group is render, PVC access is unavailable if you do not have render group present.
source /opt/intel/oneapi/setvars.sh
sycl-ls
```

The output of *sycl-ls* should show multiple lines mentioning *Data Center GPU Max*.  If this is true, you have successfully confirmed that you have access to GPUs.  Proceed to additional steps - no further testing is needed.

If you do not see *Data Center GPU Max* in your *sycl-ls* output, then we need to figure out why so you can report the right issues to support.

First, check the output of the 'groups' command. The output is a list (on one line, no commas between the names) of groups your user ID is in.  One of those names needs to be **render**.  If it is not, stop at this point and send a note to support which mentions your actual user ID something like this: "My user *uxxxxxx* is not a member of group *render* - please correct this."  To submit this see [Where to get Support](#where-to-get-support).

Second, for a variety of reasons some nodes have a nasty habit of losing track of its PVC cards - we are investigating and improving things daily (this is a *beta* after all). If you issues with nodes where PVC cards disappear (to the OS), proven by *sycl-ls* not listing them, then please let us know (see [Where to get Support](#where-to-get-support)).  Also, feel free to try other nodes (from head node, use `srun -p pvc-shared -w idc-beta-batch-pvc-node-05 --pty bash` to force yourself onto node 05 (change to try other nodes). You can see what nodes are online with `sinfo -al` and once you are on a node you can see if the cards (Intel(R) Data Center GPU Max) are by running `sycl-ls` (after you source setvars of course).
 
## VS Code Desktop Client

One can use <a href="https://code.visualstudio.com/"> VS Code</a> to connect to the IDC via the tunnels plugin which can streamline access once setup and connected.  However, VSCode has the problem of plenty with respect to plugins and sometimes they conflict.  If you have an issue please try and slim down the number of plugins.  In addition, many corporate proxies do not support web sockets.  This is best used without a proxy, YMMV.

### Overview of Steps

1. Successfully connect to IDC via SSH.  See above.
2. Have a GIT account that you can use as an OAuth provider.
3. Install Code Server on IDC in your user account.
4. Install VS Code if you do not have it. 
5. Add Remote - Tunnels Extension ID `ms-vscode.remote-server`
6. Connect to IDC worker node running VS Code Server
7. Authenticate Machine
8. Done.

Connect to IDC and get on a worker node:

```bash
ssh myidc
srun --pty bash
```

From the worker node download, unzip and execute VS Code Server, you only need to do the following the initial time.  Afterwards just execute `./code tunnel`

```bash
curl -Lk 'https://code.visualstudio.com/sha/download?build=stable&os=cli-alpine-x64' --output vscode_cli.tar.gz
tar -xzf vscode_cli
./code tunnel --accept-server-license-terms
```

Upon successful execution your screen should resemble the below screen:

![image](https://github.com/bjodom/idc/blob/main/assets/1.PNG)

As stated in the overview, you will need to have a working GitHub account:  A `ctrl+click` on the console should take you to a screen that looks like below.  Enter the code and follow the prompts.

![image](https://github.com/bjodom/idc/blob/main/assets/2.PNG)

![image](https://github.com/bjodom/idc/blob/main/assets/3.PNG)

Upon successful activation and authentication you will want to name your tunnel.  This name never needs to change and you can call it anything.  It attempts to use the machines name which is too long so shorten it.  Your screen will resemble below:

![image](https://github.com/bjodom/idc/blob/main/assets/4.PNG)

At this point launch your VS Code client, it is possible to just use a browser but you do not get the same level of functionality.  If you do not have the extension `Remote Tunnels` install it.  The extensions can be found under the 5th icon on the left of the VS Code UI.

![image](https://github.com/bjodom/idc/blob/main/assets/5.PNG)

You will likely be asked to authorize Remote - Tunnels using GitHub.  This typically only happens on the very first connection.

![image](https://github.com/bjodom/idc/blob/main/assets/6.PNG)

Follow the prompts, depending on how many organizations you belong to there could be several pages.  You do not need to authorize any of your other organizations just allow VS Code to talk to the IDC.

![image](https://github.com/bjodom/idc/blob/main/assets/7.PNG)

From VS Code Enter F1 and enter  `Remote - Tunnels: Connect to Tunnel`  Enter the name you called your tunnel.

![image](https://github.com/bjodom/idc/blob/main/assets/8.PNG)

There will be one final authorization, don't forget to check the box or you will be asked again:

![image](https://github.com/bjodom/idc/blob/main/assets/9.PNG)

At this point you should achieve a successful connection.  There will be a green box with the name of your tunnel in the lower left corner of VS Code.  

In the future all you need to do is login in to the IDC, establish the tunnel and connect to VS Code using F1 and Remote - Tunnels Connect.  



## Additional Software

It's possible to install additional software if regular user permissions are the only requirements.  For example to install <a href="https://www.intel.com/content/www/us/en/developer/articles/technical/get-started-with-intel-distribution-for-python.html">the Intel® Distribution for Python</a> follow these steps:  Miniconda is already installed, but you will be creating a virtual environment in your home directory.  

1.  `conda activate base`
2.  `conda config --add channels intel`
4.  `conda create -n idp intelpython3_full`
5.  `conda activate idp`

Keep in mind you have 20GB of storage in your home directory for all software and data.

---  
## Common Slurm Commands

```bash
sinfo -al (What Nodes are available)
PARTITION AVAIL  TIMELIMIT   JOB_SIZE ROOT OVERSUBS     GROUPS  NODES       STATE NODELIST
pvc*         up    2:00:00          1   no       NO        all      3        idle idc-beta-batch-pvc-node-[01-03]

squeue -al (How many jobs are in the queue)
JOBID PARTITION     NAME     USER    STATE       TIME TIME_LIMI  NODES NODELIST(REASON)

sbatch -p {PARTITION-NAME} {SCRIPT-NAME}
srun -p {PARTITION-NAME} {SCRIPT-NAME}
scancel {JOB-ID}

Go interactive with a compute node

srun --pty bash
```

---  
## Sample GPU Test Code

Here is a sample GPU test code that demonstrates functionality and how to offload the application execution to a `compute node`.  Follow the below steps:

Step 1.  Copy the code below into a file.

```C++
#include <sycl/sycl.hpp>
using namespace sycl;
int main() {
//# Create a device queue with device selector
  queue q(gpu_selector_v);
//# Print the device name
  std::cout << "Device: " << q.get_device().get_info<info::device::name>() << "\n";
  return 0;
}
```
Step 2.  Save the file as `getdev.cpp`

Step 3.  Enter the following commands to compile and run the application.

```bash
source /opt/intel/oneapi/setvars.sh

icpx -fsycl getdev.cpp

srun a.out
```

If successful it should return Device: Intel(R) Data Center GPU Max 1100.  Demonstrating that you successfully compiled a SYCL application and offloaded it's execution to a GPU on the compute node.

---  
## An Example Script

This will email you at the start and completion of your job.  

```bash
#!/bin/bash
#SBATCH --job-name=gpu_run
#SBATCH --partition=pvc-shared
#SBATCH --error=job.%J.err 
#SBATCH --output=job.%J.out
#SBATCH --mail-type=ALL
#SBATCH --mail-user=your@emai.com

srun ./my_a.out
```

---  
## Running MPI

When using MPI, you should set these environment variables (put in your ~/.bashrc to always have them):
```bash
export I_MPI_PORT_RANGE=50000:50500
export btl_tcp_port_min_v4=1024
```

MPI is currently limited to a single node, and must be run without SLURM.  Since SLURM (srun) will be the default, you need to specify a different launcher using the -launcher option.

For instance - either of these should work:
```bash
mpirun -launcher ssh -n 128 ./a.out
mpirun -launcher fork -n 128 ./a.out
```

These are probably the same (ssh and fork), but honestly we don't know.  They seem to run in the same time.  Let us know if you decide one is a superior choice.

Instead of using the -launcher option, you can also unset the environment variables that trigger mpirun to use SLURM.  To do so, use:
```bash
unset SLURM_TASKS_PER_NODE
unset SLURM_JOBID
```
Unfortunately, adding these to your ~/.bashrc will not work becasue they are added into your environment later than that.  But, you can issue manually before you use mpirun if you want to avoid the -launcher option.

Visit the [MPI with SYCL example page](etc/MPI.md) for a quick example of how to get a SYCL Hello World from 40 different connections to GPUs (40 ranks).

---
## If you use MobaXterm

If you like using ModaXterm, here are notes from a user (thank you Yuning!) on the steps to make it fully work:

Step 1: Get ip address  

echo $(ip a | grep -v -e "127.0.0.1" -e "inet6" | grep "inet" | awk {'print($2)}' | sed 's/\/.*//') 

example output: 10.10.10.8 

Step2: Select the tunneling tab in MobaXterm

![image](https://github.com/jamesreinders/idc/assets/6556265/9d3f1d5b-8171-41c0-a7bd-8fa5bebc9592)

Select your own private key 

![image](https://github.com/jamesreinders/idc/assets/6556265/0bd39143-398c-4977-a423-203d2b563b02)

Description automatically generated 

![image](https://github.com/jamesreinders/idc/assets/6556265/162da683-30d1-43a7-a309-452aac529293)

If you need a proxy (Intel employees do when on internal network or VPN) - set up proxy (Intel is “proxy-dmz.intel.com:1080”). 

![image](https://github.com/jamesreinders/idc/assets/6556265/1431243b-30b4-4e29-841f-dc8b4c959d45)

Edit this tunnel 

![image](https://github.com/jamesreinders/idc/assets/6556265/06dd5c30-f4ea-401f-b147-3ead4d051fc8)

Step3: Launch Jupyter notebook in MobaXterm (use the IP address 10.10.10.X you were assigned)

jupyter-lab --ip 10.10.10.X --no-browser   

---
## VTune, Advisor, PTrace - and other things you will get later

VTune, Advisor, and PTrace will come later - not now.
We will not install or offer tools that give system wide insight, due to serious security concerns that exist when you have a very diverse community of users.
This means that VTune, Advisor, and PTrace will not be installed or activated.
We do plan to offer more isolated systems in the future which will host these highly useful tools.  We love them and it pains us to have to leave them off these systems.

---
## FAQs: Super Important Tips that may be non-obvious

Please read these carefully, many may solve obstacles you encounter.

1. **Incoming only ssh/fstp/scp:** Your ~/.ssh directory is owned by root.  Please leave it alone, changing it would not do what you hope.  You can use https in and out (e.g., git). However, ssh, sftp, scp, etc. are incoming only.  You can use the -L option on your ssh into the instance to connect your machine nicely into the instance.  If you cannot figure out how to get this working, or feel it is too limiting - reach out to us to [discuss via request support - see instructions.](#where-to-get-support)
2. **Do not forget /tmp:** Your account has (only) 20G of persistent storage (available on all nodes, and persists between logins). For more high speed temporary space, try using /tmp. Of course, /tmp may be wiped clean by a reboot - it should survive on a node otherwise. If you need to reconnect, you may need to specify the node you need to attach to using an additional option on srun such as -w idc-beta-batch-pvc-node-XX (you need to know which node XX to specify).  If there is popular dataset, or tool, you want available globally - reach out to us to [make suggestion via request support - see instructions.](#where-to-get-support)
3. **Do remember /tmp is NOT PERMANENT** all files in /tmp will disappear without notice (reboots) - so its a great place to use extra space for a brief time, but don't do work there that is not easily recreated
4. **Renew your access before it expires:** We cannot restore files if you let your access expire - they really are lost. We recommend you [Extend your access](#extend-access)) in the week preceeding expiration, and due to a bug (see next section) you really do not want to use it on the last day. Of course, even if it expires you can create another instance and recreate your environment/files.
5. **If your ssh fails** the two most common causes are: (a) incorrect ssh folder and file permissions, (b) being out of sync with the instance.  For the first (a), refer to [SSH folder and file permissions](#ssh-permissions). For the latter (b), go to https://scheduler.cloud.intel.com ([click here to see the screenshots on how to do](#put-key-in)) and put your public key in your profile (to be sure it matches the one you are using on your systme) and then launch a new instance.
6. **Publish results:** We welcome you publishing results you get from using Intel Developer Cloud. Of course, if you see anything unexpected we would welcome [questions via request support - see instructions.](#where-to-get-support). We enjoy seeing mention if you enjoyed using the Intel Developer Cloud, and we encourage you to use the exclusive queue to get performance numbers without others on the system you are running upon. The systems with PCIe cards are 1100 (single tile) GPUs, and we will eventually also have 1550 (dual tile) GPUs. Noting which model you used is encouraged too.
7. **GDB** gdb is called via gdb-oneapi. This version will enable you to debug on CPU and GPU.  

