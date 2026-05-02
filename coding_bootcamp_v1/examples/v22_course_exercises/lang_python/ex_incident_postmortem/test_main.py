import subprocess, sys
def test_expected_token():
    result = subprocess.run([sys.executable, "main.py"], capture_output=True, text=True, check=True)
    assert "PASS_INCIDENT_POSTMORTEM" in result.stdout
