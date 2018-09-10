export DEVICE=$(ls /dev/tty* | grep ACM)
echo "Il dispositivo e' $DEVICE"
export FLASK_APP=server.py
python -m flask run --host=0.0.0.0