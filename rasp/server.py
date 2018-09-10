from json import dumps
from flask import Flask, request
from arduino import sendCommand

app = Flask(__name__)

@app.route('/command', methods=['POST'])
def manageCommand():
    print(request.form['command'])
    sendCommand(request.form['command'])
    return dumps({'success':True}), 200, {'ContentType':'application/json'} 