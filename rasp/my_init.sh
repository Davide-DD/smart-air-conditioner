export DEVICE=$(ls /dev/tty* | grep ACM)
echo "Il dispositivo e' $DEVICE"
cd /home/pi/SmartHome
export FLASK_APP=server.py
python -m flask run --host=0.0.0.0