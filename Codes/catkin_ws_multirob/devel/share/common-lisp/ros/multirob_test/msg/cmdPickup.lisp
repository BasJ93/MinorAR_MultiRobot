; Auto-generated. Do not edit!


(cl:in-package multirob_test-msg)


;//! \htmlinclude cmdPickup.msg.html

(cl:defclass <cmdPickup> (roslisp-msg-protocol:ros-message)
  ((source
    :reader source
    :initarg :source
    :type cl:string
    :initform "")
   (destination
    :reader destination
    :initarg :destination
    :type cl:string
    :initform "")
   (amount
    :reader amount
    :initarg :amount
    :type cl:integer
    :initform 0))
)

(cl:defclass cmdPickup (<cmdPickup>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <cmdPickup>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'cmdPickup)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name multirob_test-msg:<cmdPickup> is deprecated: use multirob_test-msg:cmdPickup instead.")))

(cl:ensure-generic-function 'source-val :lambda-list '(m))
(cl:defmethod source-val ((m <cmdPickup>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader multirob_test-msg:source-val is deprecated.  Use multirob_test-msg:source instead.")
  (source m))

(cl:ensure-generic-function 'destination-val :lambda-list '(m))
(cl:defmethod destination-val ((m <cmdPickup>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader multirob_test-msg:destination-val is deprecated.  Use multirob_test-msg:destination instead.")
  (destination m))

(cl:ensure-generic-function 'amount-val :lambda-list '(m))
(cl:defmethod amount-val ((m <cmdPickup>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader multirob_test-msg:amount-val is deprecated.  Use multirob_test-msg:amount instead.")
  (amount m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <cmdPickup>) ostream)
  "Serializes a message object of type '<cmdPickup>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'source))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'source))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'destination))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'destination))
  (cl:let* ((signed (cl:slot-value msg 'amount)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <cmdPickup>) istream)
  "Deserializes a message object of type '<cmdPickup>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'source) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'source) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'destination) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'destination) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'amount) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<cmdPickup>)))
  "Returns string type for a message object of type '<cmdPickup>"
  "multirob_test/cmdPickup")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmdPickup)))
  "Returns string type for a message object of type 'cmdPickup"
  "multirob_test/cmdPickup")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<cmdPickup>)))
  "Returns md5sum for a message object of type '<cmdPickup>"
  "cb7b87605e8df0a7af0a85afc4740a0a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'cmdPickup)))
  "Returns md5sum for a message object of type 'cmdPickup"
  "cb7b87605e8df0a7af0a85afc4740a0a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<cmdPickup>)))
  "Returns full string definition for message of type '<cmdPickup>"
  (cl:format cl:nil "string source~%string destination~%int32 amount~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'cmdPickup)))
  "Returns full string definition for message of type 'cmdPickup"
  (cl:format cl:nil "string source~%string destination~%int32 amount~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <cmdPickup>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'source))
     4 (cl:length (cl:slot-value msg 'destination))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <cmdPickup>))
  "Converts a ROS message object to a list"
  (cl:list 'cmdPickup
    (cl:cons ':source (source msg))
    (cl:cons ':destination (destination msg))
    (cl:cons ':amount (amount msg))
))
