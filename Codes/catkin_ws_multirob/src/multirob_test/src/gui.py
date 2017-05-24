#!/usr/bin/env python

#example window creation with pygtk

import sys
import rospy
import rospkg

from multirob_test.msg import cmdPickup

import pygtk
pygtk.require('2.0')
import gtk

pathLocations = "blah"

class guiElements:
    def sendCommand(self, widget):
        if not rospy.is_shutdown():
            self.cmd_pub.publish(self.comboBoxSource.get_active_text(), self.comboBoxDestination.get_active_text(), self.product.get_text(), int(self.amount.get_text()))
        else:
            print("Rospy is shutdown")
        #print self.comboBoxSource.get_active_text()
        #print self.comboBoxDestination.get_active_text()
        #print self.amount.get_text()
        #print int(self.amount.get_text())
        
    def destroy(self, widget, data=None):
        sys.exit(0)#gtk.main_quit()

    def __init__(self):
        self.cmd_pub = rospy.Publisher("pickup_command", cmdPickup, queue_size=0)
        
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect("destroy", self.destroy)
        self.window.set_border_width(10)
                
        self.comboBoxSource = gtk.combo_box_new_text()
        self.comboBoxSource.append_text("Select Source")
        self.comboBoxDestination = gtk.combo_box_new_text()
        self.comboBoxDestination.append_text("Select Destination")
        
        with open(pathLocations) as f:
            for line in f:
                #print line
                line.split('\t')
                self.comboBoxSource.append_text(line[0])
                self.comboBoxDestination.append_text(line[0])
                if 'str' in line:
                    break
                
        self.comboBoxSource.set_active(0)
        self.comboBoxDestination.set_active(0)

        self.amount = gtk.Entry(max=0)

        self.product = gtk.Entry(max=0)
        self.product.set_text("test")

        self.button = gtk.Button("Send")
        self.button.connect("clicked", self.sendCommand)
        
        self.labelSource = gtk.Label("Source:")
        self.labelDestination = gtk.Label("Destination:")
        self.labelAmount = gtk.Label("Amount:")
        self.labelProduct = gtk.Label("Product:")        
        
        self.box = gtk.VBox(False, 0)
        self.box.add(self.labelSource)        
        self.box.add(self.comboBoxSource)
        self.box.add(self.labelDestination)
        self.box.add(self.comboBoxDestination)
        self.box.add(self.labelAmount)
        self.box.add(self.amount)
        self.box.add(self.labelProduct)
        self.box.add(self.product)
        self.box.add(self.button)
        self.labelSource.show()
        self.labelDestination.show()
        self.labelAmount.show()
        self.labelProduct.show()
        self.button.show()
        self.amount.show()
        self.comboBoxSource.show()
        self.comboBoxDestination.show()
        self.product.show()

        self.window.add(self.box)
        self.box.show()
        self.window.show()
        
    def main(self):
        gtk.main()

#print __name__
if __name__ == "__main__":
    rospy.init_node('multirob_test_gui', anonymous=True)
    rospack = rospkg.RosPack()

    packagePath = rospack.get_path("multirob_test")
    pathLocations = packagePath + "/locations/locations.txt"
        
    gui = guiElements()
    #gui.main()
    while (gtk.main_iteration(block=False)):
        rospy.sleep(-1)
        #rospy.spinOnce()