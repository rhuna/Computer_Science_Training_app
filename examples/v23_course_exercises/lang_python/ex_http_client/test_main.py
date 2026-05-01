import subprocess, sys
def test_expected_token():
    result = subprocess.run([sys.executable, "main.py"], capture_output=True, text=True, check=True)
    assert "PASS_HTTP_CLIENT" in result.stdout
