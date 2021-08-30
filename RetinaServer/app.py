import os
from flask import Flask, request
from werkzeug.utils import secure_filename

UPLOAD_FOLDER = '/home/leonardo/tests/images'
ALLOWED_EXTENSIONS = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route('/hello')
def hello():
    return 'Hello World'

@app.route('/test_sendHttp', methods=['GET', 'POST'])
def print_sendHttp():
    if request.method == 'POST':
        formData_dict = request.form.to_dict()
        
        # if there is a file with 'Image' key
        if request.files['Image']:
            file = request.files['Image']
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        
        return formData_dict, 200
      

    return "Success GET", 200

@app.route('/test_getStorage', methods=['GET', 'POST'])
def print_getStorage():
    status = "0"
    # status = '1'

    return status, 200

@app.route('/test_triggerLED', methods=['GET', 'POST'])
def test_triggerLED():
    if request.method == 'POST':
        formData_dict = request.form.to_dict()
        
        return formData_dict, 200
      

    return "Success GET", 200


if __name__ == "__main__":
    app.run(debug=True, port=5000)