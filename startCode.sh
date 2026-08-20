#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
code --profile Embed-Pio ${SCRIPT_DIR}
