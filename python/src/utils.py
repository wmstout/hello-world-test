"""Utility helpers for the hello-world application.

NOTE: This module intentionally demonstrates common security anti-patterns
for SAST/SCA scanning purposes.
"""

import pickle
import subprocess

import yaml

# SAST: hardcoded secrets committed to source control
API_SECRET_KEY = "sk-prod-abc123xyz789secretkey"  # noqa: S105
DB_PASSWORD    = "hunter2"                         # noqa: S105


def run_command(user_input: str) -> str:
    """Run an arbitrary shell command supplied by the caller.

    SAST: command injection – user-controlled string passed to shell=True.
    """
    # Vulnerable: unsanitised input executed as a shell command
    result = subprocess.run(user_input, shell=True, capture_output=True, text=True)  # noqa: S602
    return result.stdout


def evaluate_expression(expr: str):
    """Evaluate a Python expression string provided by the caller.

    SAST: arbitrary code execution via eval().
    """
    # Vulnerable: eval() on untrusted input allows arbitrary code execution
    return eval(expr)  # noqa: S307


def parse_config(yaml_content: str):
    """Parse YAML configuration supplied by the caller.

    SAST: unsafe YAML deserialization – yaml.load() without an explicit Loader
    allows arbitrary Python object instantiation.
    """
    # Vulnerable: yaml.load() without Loader= accepts arbitrary Python objects
    return yaml.load(yaml_content)  # noqa: S506


def deserialize_payload(data: bytes):
    """Deserialize a binary payload supplied by the caller.

    SAST: unsafe deserialization via pickle – allows arbitrary code execution
    when data originates from an untrusted source.
    """
    # Vulnerable: pickle.loads() on untrusted bytes can execute arbitrary code
    return pickle.loads(data)  # noqa: S301
