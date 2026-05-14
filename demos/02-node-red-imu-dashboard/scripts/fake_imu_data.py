"""
Fake IMU telemetry source for the Node-RED embedded logger demo.

Connects to a TCP server (Node-RED 'tcp in' node, default 127.0.0.1:5000)
and streams ASCII lines that look like what real firmware would print:

    AX=0.123;AY=-0.456;AZ=0.987

Values move slowly (sin/cos of wall-clock time) with a small noise term so
the dashboard chart looks alive but not chaotic. ~10 Hz by default.

Standard library only — runs on any Python 3.8+ with no extra installs.

Stop with Ctrl+C.
"""

import argparse
import math
import random
import socket
import sys
import time


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Fake IMU TCP source")
    p.add_argument("--host", default="127.0.0.1", help="Node-RED host")
    p.add_argument("--port", type=int, default=5000, help="Node-RED tcp-in port")
    p.add_argument("--rate", type=float, default=10.0, help="samples per second")
    p.add_argument(
        "--noise",
        type=float,
        default=0.02,
        help="±noise amplitude added to each axis (in g)",
    )
    return p.parse_args()


def sample(t: float, noise: float) -> tuple[float, float, float]:
    ax = 0.20 * math.sin(t * 1.0) + noise * (random.random() - 0.5)
    ay = 0.20 * math.cos(t * 0.7) + noise * (random.random() - 0.5)
    az = 1.00 + 0.05 * math.sin(t * 0.3) + noise * (random.random() - 0.5)
    return ax, ay, az


def main() -> int:
    args = parse_args()
    period = 1.0 / args.rate

    print(f"Connecting to {args.host}:{args.port} ...", file=sys.stderr)
    try:
        sock = socket.create_connection((args.host, args.port), timeout=5.0)
    except OSError as e:
        print(f"connect failed: {e}", file=sys.stderr)
        print(
            "Hint: start Node-RED and deploy a flow with a 'tcp in' node "
            f"listening on port {args.port}.",
            file=sys.stderr,
        )
        return 1

    print(
        f"Connected. Streaming {args.rate:g} Hz. Press Ctrl+C to stop.",
        file=sys.stderr,
    )
    sock.settimeout(None)

    t0 = time.monotonic()
    try:
        while True:
            t = time.monotonic() - t0
            ax, ay, az = sample(t, args.noise)
            line = f"AX={ax:.3f};AY={ay:.3f};AZ={az:.3f}\n"
            sock.sendall(line.encode("ascii"))
            time.sleep(period)
    except KeyboardInterrupt:
        print("\nStopped by user.", file=sys.stderr)
    except (BrokenPipeError, ConnectionResetError) as e:
        print(f"\nConnection lost: {e}", file=sys.stderr)
        return 2
    finally:
        try:
            sock.close()
        except OSError:
            pass

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
