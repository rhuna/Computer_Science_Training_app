import subprocess, sys
def test_expected_token():
    result = subprocess.run([sys.executable, "main.py"], capture_output=True, text=True, check=True)
    assert "PASS_RAG_DESIGN_DOC" in result.stdout
