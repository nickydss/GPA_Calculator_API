from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import json

app = Flask(__name__)
CORS(app)

@app.route('/gpa', methods=['POST'])
def calculate_gpa():
    input_data = request.get_json()
    print("Received data:", input_data)
    proc = subprocess.Popen(
        ['./gpa_calculator'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        text=True
    )
    stdout, _ = proc.communicate(json.dumps(input_data))
    result = json.loads(stdout)
    print("GPA calculation result:", result)
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)
