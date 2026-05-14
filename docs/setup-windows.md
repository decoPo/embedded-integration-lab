# Setup on Windows

Tested on Windows 11 with Node.js 24 LTS, Node-RED 4.1, Dashboard 2.0
(`@flowfuse/node-red-dashboard` 1.30) and `node-red-node-serialport` 2.0.
No Docker, MSYS or WSL needed.

## 1. Install Node.js LTS

Download the LTS installer from <https://nodejs.org> and run it with the
defaults.

Verify in PowerShell:

```powershell
node -v
npm -v
```

Both should print a version.

## 2. Allow `npm` scripts in PowerShell

If `npm` errors with *running scripts is disabled on this system*, open
**PowerShell as Administrator** once and run:

```powershell
Set-ExecutionPolicy RemoteSigned
```

Confirm with `A`. One-time only.

## 3. Install Node-RED

```powershell
npm install -g --unsafe-perm node-red
```

Start it:

```powershell
node-red
```

Open <http://127.0.0.1:1880> — the flow editor should load.

## 4. Install Dashboard 2.0 and serialport

We use **Dashboard 2.0** (`@flowfuse/node-red-dashboard`, Vue 3) — *not*
the deprecated classic `node-red-dashboard`. They use different node names
(`ui-chart` vs `chart`, etc.) and different URLs (`/dashboard` vs `/ui`).

Easiest way: install from inside Node-RED.

1. Menu (top-right ☰) → **Manage palette** → tab **Install**.
2. Search and install:
   - `@flowfuse/node-red-dashboard`
   - `node-red-node-serialport`
3. Close the dialog. Restart Node-RED if it asks (Ctrl+C in the terminal,
   then `node-red` again).

Or from the command line:

```powershell
cd $env:USERPROFILE\.node-red
npm install @flowfuse/node-red-dashboard node-red-node-serialport
```

The dashboard will then be available at <http://127.0.0.1:1880/dashboard>.

## 5. Sanity check (no hardware)

In the editor, drag in:

```
inject  ──▶  debug
```

Click **Deploy**, then click the inject button. The debug pane on the right
should print a timestamp. If that works, the install is healthy.

This is exactly what
[`demos/01-hello-world-inject/`](../demos/01-hello-world-inject/) imports
as a ready-made flow.

## Next

Continue with [`demos/02-node-red-imu-dashboard/`](../demos/02-node-red-imu-dashboard/).
