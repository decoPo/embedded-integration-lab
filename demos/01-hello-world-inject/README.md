# 01 — Hello-world: inject → debug

The smallest possible Node-RED flow. Used as the very first live step in the
talk to show the editor, the deploy cycle and the debug sidebar before any
hardware or dashboard is involved.

```
inject (every 1 s)  ──▶  debug (timestamp)
```

## Run

1. Install Node-RED (see [`docs/setup-windows.md`](../../docs/setup-windows.md)).
2. Start it (`node-red`) and open <http://127.0.0.1:1880>.
3. Menu → **Import** → paste the contents of [`flows.json`](flows.json) →
   **Import**.
4. **Deploy**.
5. Open the **debug** sidebar (bug icon on the right). A timestamp should
   appear once per second.

That is the entire demo. It is intentionally trivial — its only job is to
prove the install works before moving on to [demo 02](../02-node-red-imu-dashboard/).
