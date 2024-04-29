from flask import Flask, jsonify, request
# to run the c file from python we require the subprocess module
import subprocess
# cors
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

 
@app.route('/upload', methods=['POST'])
def upload():
    # we are storing the file in msg.txt
    f = request.files['file']
    f.save("msg.txt")
    subprocess.run(["gcc", "huffman.c"])
    subprocess.run(["./a.out", "msg.txt"])
    with open("encoded.txt", "r") as f:
        encoded = f.read()
    with open("decoded.txt", "r") as f:
        decoded = f.read()
    return jsonify({"encoded": encoded, "decoded": decoded})
    


if __name__ == '__main__':
    app.run(debug=True)