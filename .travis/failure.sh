#!/usr/bin/env bash

set -euxo pipefail

wget https://raw.githubusercontent.com/DiscordHooks/travis-ci-discord-webhook/master/send.sh
chmod +x send.sh
./send.sh failure $WEBHOOK_URL
