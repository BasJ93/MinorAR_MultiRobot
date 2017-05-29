
(cl:in-package :asdf)

(defsystem "multirob_test-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "cmdPickup" :depends-on ("_package_cmdPickup"))
    (:file "_package_cmdPickup" :depends-on ("_package"))
    (:file "r2rpickupresponse" :depends-on ("_package_r2rpickupresponse"))
    (:file "_package_r2rpickupresponse" :depends-on ("_package"))
  ))