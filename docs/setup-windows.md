# Setup on Windows

Tested on Windows 11. Should also work on Windows 10. The steps below are
deliberately minimal — no Docker, no MSYS, no WSL needed.

## 1. Install Node.js LTS

Download the LTS installer from <https://nodejs.org> and run it with the
defaults.

Verify in PowerShell:

```powershell
node -v
npm -v
```

Both commands should print a version.

## 2. Allow `npm` to run in PowerShell

If running `npm` produces a `running scripts is disabled on this system`
error, open **PowerShell as Administrator** once and run:

```powershell
Set-ExecutionPolicy RemoteSigned
```

Confirm with `A` (Yes to All). This is a one-time step.

## 3. Install Node-RED

```powershell
npm install -g --unsafe-perm node-red
```

Start it:

```powershell
node-red
```

Open <http://127.0.0.1:1880> — the flow editor should load.

## 4. Install the dashboard plugin

In a new terminal:

```powershell
cd $env:USERPROFILE\.node-red
npm install node-red-dashboard
```

Restart Node-RED (Ctrl+C in the original terminal, then `node-red` again).

The dashboard is then available at <http://127.0.0.1:1880/ui>.

## 5. (Optional) Install the serial-port plugin

Some Node-RED installs already include a serial node. If the *serial in* and
*serial out* nodes are missing from the palette:

```powershell
cd $env:USERPROFILE\.node-red
npm install node-red-node-serialport
```

Restart Node-RED again.

## 6. Sanity-check flow (no hardware needed)

In the editor, drag in:

```
inject  ──▶  debug
```

Click *Deploy*, then click the inject button. The debug pane on the right
should print a timestamp. If that works, the install is healthy and the
demo flow can be imported.

## Next

Continue with [`demos/01-node-red-embedded-logger/`](../demos/01-node-red-embedded-logger/).
