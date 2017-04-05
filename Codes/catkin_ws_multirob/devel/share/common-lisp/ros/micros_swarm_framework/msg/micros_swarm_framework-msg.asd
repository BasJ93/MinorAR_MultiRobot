
(cl:in-package :asdf)

(defsystem "micros_swarm_framework-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "MSFPPacket" :depends-on ("_package_MSFPPacket"))
    (:file "_package_MSFPPacket" :depends-on ("_package"))
  ))