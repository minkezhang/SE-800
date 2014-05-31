package com.game.src.main;

import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class MouseInput implements MouseListener{

	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		int mx = e.getX();
		int my = e.getY();
		/**
		public Rectangle playbut = new Rectangle(Game.WIDTH/2 +120,150,100,50);
		public Rectangle helpbut = new Rectangle(Game.WIDTH/2 +120,250,100,50);
		public Rectangle quitbut = new Rectangle(Game.WIDTH/2 +120,350,100,50);
		 */
		
		//Play
		if(mx >= Game.WIDTH / 2 + 120 && mx <= Game.WIDTH/2 + 220){
			if(my >= 150 && my <= 200){
				//pressed play
				//Game.State = Game.STATE.GAME;
				this.run();
			}
		}
		//Quit
				if(mx >= Game.WIDTH / 2 + 120 && mx <= Game.WIDTH/2 + 220){
					if(my >= 350 && my <= 400){
						//quit game
						System.exit(1);
					}
				}
	}

	private void run() {
		try
		{
		Runtime rt = Runtime.getRuntime();
		//Process p = rt.exec("C:\\Windows\\System32\\notepad.exe");
		Process p = Runtime.getRuntime().exec(new String[] {"./se800", "server", "6667"});
		Process q = Runtime.getRuntime().exec(new String[] {"./se800", "client", "6667", "127.0.0.1"});
		  /*try {
			    Robot r = new Robot();
			    r.keyPress(KeyEvent.VK_ALT);
			    r.keyPress(KeyEvent.VK_TAB);
			    r.delay(10); //set the delay
			    r.keyRelease(KeyEvent.VK_ALT);
			    r.keyRelease(KeyEvent.VK_TAB);
			  } catch(AWTException e) {
			    // handle
			  }*/
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
