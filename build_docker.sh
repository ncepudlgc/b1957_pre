#!/bin/bash
NAMESPACE="${1:-codebase_b1957_app}"
docker build -t "$NAMESPACE" .