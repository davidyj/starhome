package com.example.sample_character;

import java.util.HashMap;

import org.cocos2d.nodes.Animation;

public class CPlayerAnimation  {

	private int character;
	private float interval = 0.1f;
	private HashMap<String, Animation> body = new HashMap<String, Animation>();
	private HashMap<String, Animation> arm = new HashMap<String, Animation>();
	private HashMap<String, Animation> armoverhair = new HashMap<String, Animation>();
	private HashMap<String, Animation> lhand = new HashMap<String, Animation>();
	private HashMap<String, Animation> rhand = new HashMap<String, Animation>();
	private HashMap<String, Animation> hand = new HashMap<String, Animation>();
	
	public void CPlayerAnimation(int character){
		
		Animation ani = null;
		//alter
		ani = new Animation("alter",interval);
		ani.addFrame("character_00002000_alert_0_body.png");
		ani.addFrame("character_00002000_alert_1_body.png");
		ani.addFrame("character_00002000_alert_2_body.png");
		body.put("alter", ani);
		
		ani = new Animation("alter",interval);
		ani.addFrame("character_00002000_alert_0_arm.png");
		ani.addFrame("character_00002000_alert_1_arm.png");
		ani.addFrame("character_00002000_alert_2_arm.png");
		arm.put("alter",ani);
		
		Animation lhandAni = new Animation("alter",interval);
		lhandAni.addFrame("character_00002000_alert_0_lhand¡£png");
		lhandAni.addFrame("character_00002000_alert_1_lhand.png");
		lhandAni.addFrame("character_00002000_alert_2_lhand.png");
		lhand.put("alter",lhandAni);
		
		ani = new Animation("alter",interval);
		ani.addFrame("character_00002000_alert_0_rhand.png");
		ani.addFrame("character_00002000_alert_1_rhand.png");
		ani.addFrame("character_00002000_alert_2_rhand.png");
		rhand.put("alter",ani);
		
		//dead
		ani = new Animation("dead",interval);
		ani.addFrame("character_00002000_dead_0_body.png");
		body.put("dead", ani);
		
		//fly
		ani = new Animation("fly",interval);
		ani.addFrame("character_00002000_fly_0_body.png");
		ani.addFrame("character_00002000_fly_1_body.png");		
		body.put("fly",ani);
		
		ani = new Animation("fly",interval);
		ani.addFrame("character_00002000_fly_0_arm.png");
		ani.addFrame("character_00002000_fly_1_arm.png");		
		arm.put("fly",ani);
		
		ani = new Animation("fly",interval);
		ani.addFrame("character_00002000_fly_0_lhand.png");
		ani.addFrame("character_00002000_fly_1_lhand.png");		
		lhand.put("fly",ani);
		
		ani = new Animation("fly",interval);
		ani.addFrame("character_00002000_fly_0_rhand.png");
		ani.addFrame("character_00002000_fly_1_rhand.png");		
		rhand.put("fly",ani);
		
		//heal
		ani = new Animation("heal",interval);
		ani.addFrame("character_00002000_heal_1_body.png");				
		body.put("heal",ani);
		
		ani = new Animation("heal",interval);
		ani.addFrame("character_00002000_heal_1_arm.png");				
		arm.put("heal",ani);
		
		//jump
		ani = new Animation("jump",interval);
		ani.addFrame("character_00002000_jump_0_body.png");				
		body.put("jump",ani);
		
		ani = new Animation("jump",interval);
		ani.addFrame("character_00002000_jump_0_arm.png");				
		arm.put("jump",ani);
		
		ani = new Animation("jump",interval);
		ani.addFrame("character_00002000_jump_0_lhand.png");				
		lhand.put("jump",ani);
		
		ani = new Animation("jump",interval);
		ani.addFrame("character_00002000_jump_0_rhand.png");				
		rhand.put("jump",ani);
		
		//ladder
		ani = new Animation("ladder",interval);
		ani.addFrame("character_00002000_ladder_0_body.png");
		ani.addFrame("character_00002000_ladder_1_body.png");
		body.put("ladder",ani);
		
		//personstab
		ani = new Animation("personstab",interval);
		ani.addFrame("character_00002000_pronestab_0_body.png");
		ani.addFrame("character_00002000_pronestab_1_body.png");
		body.put("personstab",ani);
		
		ani = new Animation("personstab",interval);
		ani.addFrame("character_00002000_pronestab_0_arm.png");
		ani.addFrame("character_00002000_pronestab_1_arm.png");
		arm.put("personstab",ani);
		
		//rope
		ani = new Animation("ladder",interval);
		ani.addFrame("character_00002000_rope_0_body.png");
		ani.addFrame("character_00002000_rope_1_body.png");
		body.put("ladder",ani);
		
		//shoot1
		ani = new Animation("shoot1",interval);
		ani.addFrame("character_00002000_shoot1_0_body.png");
		ani.addFrame("character_00002000_shoot1_1_body.png");
		body.put("shoot1",ani);
		
		ani = new Animation("shoot1",interval);
		ani.addFrame("character_00002000_shoot1_0_arm.png");
		ani.addFrame("character_00002000_shoot1_1_arm.png");
		arm.put("shoot1",ani);
		
		//shoot2
		ani = new Animation("shoot2",interval);
		ani.addFrame("character_00002000_shoot2_0_body.png");
		ani.addFrame("character_00002000_shoot2_1_body.png");
		ani.addFrame("character_00002000_shoot2_2_body.png");
		ani.addFrame("character_00002000_shoot2_3_body.png");
		ani.addFrame("character_00002000_shoot2_4_body.png");
		body.put("shoot2",ani);
		
		ani = new Animation("shoot2",interval);
		ani.addFrame("character_00002000_shoot2_0_arm.png");
		ani.addFrame("character_00002000_shoot2_1_arm.png");
		ani.addFrame("character_00002000_shoot2_2_arm.png");
		ani.addFrame("character_00002000_shoot2_3_arm.png");
		ani.addFrame("character_00002000_shoot2_4_arm.png");		
		arm.put("shoot2",ani);
		
		//shootf
		ani = new Animation("shootf",interval);
		ani.addFrame("character_00002000_shoof_0_body.png");
		ani.addFrame("character_00002000_shoof_1_body.png");
		body.put("shootf",ani);
		
		ani = new Animation("shootf",interval);
		ani.addFrame("character_00002000_shootf_0_arm.png");
		ani.addFrame("character_00002000_shootf_1_arm.png");
		arm.put("shootf",ani);
		
		//sit
		ani = new Animation("sit",interval);
		ani.addFrame("character_00002000_sit_0_body.png");
		body.put("sit",ani);
		
		ani = new Animation("sit",interval);
		ani.addFrame("character_00002000_sit_0_arm.png");
		arm.put("sit",ani);
		
		//stabo1
		ani = new Animation("stabo1",interval);
		ani.addFrame("character_00002000_stabo1_0_body.png");
		ani.addFrame("character_00002000_stabo1_1_body.png");
		body.put("stabo1",ani);
		
		ani = new Animation("stabo1",interval);
		ani.addFrame("character_00002000_stabo1_0_arm.png");
		ani.addFrame("character_00002000_stabo1_1_arm.png");
		arm.put("stabo1",ani);
		
		//stabo2
		ani = new Animation("stabo2",interval);
		ani.addFrame("character_00002000_stabo2_0_body.png");
		ani.addFrame("character_00002000_stabo2_1_body.png");
		body.put("stabo2",ani);
		
		ani = new Animation("stabo2",interval);
		ani.addFrame("character_00002000_stabo2_0_arm.png");
		ani.addFrame("character_00002000_stabo2_1_arm.png");
		arm.put("stabo2",ani);
		
		//stabof
		ani = new Animation("stabof",interval);
		ani.addFrame("character_00002000_stabof_0_body.png");
		ani.addFrame("character_00002000_stabof_1_body.png");
		ani.addFrame("character_00002000_stabof_2_body.png");
		body.put("stabof",ani);
		
		ani = new Animation("stabof",interval);
		ani.addFrame("character_00002000_stabof_0_arm.png");
		ani.addFrame("character_00002000_stabof_1_arm.png");
		ani.addFrame("character_00002000_stabof_2_arm.png");
		arm.put("stabof",ani);
		
		//stabt1
		ani = new Animation("stabt1",interval);
		ani.addFrame("character_00002000_stabt1_0_body.png");
		ani.addFrame("character_00002000_stabt1_1_body.png");
		ani.addFrame("character_00002000_stabt1_2_body.png");
		body.put("stabt1",ani);
		
		ani = new Animation("stabt1",interval);
		ani.addFrame("character_00002000_stabt1_0_arm.png");
		ani.addFrame("character_00002000_stabt1_1_arm.png");
		ani.addFrame("character_00002000_stabt1_2_arm.png");
		arm.put("stabt1",ani);
		
		ani = new Animation("stabt1",interval);
		ani.addFrame("character_00002000_stabt1_0_hand.png");
		ani.addFrame("character_00002000_stabt1_1_hand.png");
		ani.addFrame("character_00002000_stabt1_2_hand.png");
		hand.put("stabt1",ani);
		
		//stabt2
		ani = new Animation("stabt2",interval);
		ani.addFrame("character_00002000_stabt2_0_body.png");
		ani.addFrame("character_00002000_stabt2_1_body.png");
		ani.addFrame("character_00002000_stabt2_2_body.png");
		body.put("stabt2",ani);
		
		ani = new Animation("stabt2",interval);
		ani.addFrame("character_00002000_stabt2_0_arm.png");
		ani.addFrame("character_00002000_stabt2_1_arm.png");
		ani.addFrame("character_00002000_stabt2_2_arm.png");
		arm.put("stabt2",ani);
		
		ani = new Animation("stabt2",interval);
		ani.addFrame("character_00002000_stabt2_0_hand.png");
		ani.addFrame("character_00002000_stabt2_1_hand.png");
		ani.addFrame("character_00002000_stabt2_2_hand.png");
		hand.put("stabt2",ani);
		
		//stabtf
		ani = new Animation("stabtf",interval);
		ani.addFrame("character_00002000_stabtf_2_arm.png");
		arm.put("stabtf",ani);
		
		ani = new Animation("stabtf",interval);
		ani.addFrame("character_00002000_stabtf_2_armoverhair.png");
		armoverhair.put("stabtf",ani);
		
		ani = new Animation("stabtf",interval);
		ani.addFrame("character_00002000_stabtf_2_body.png");
		body.put("stabtf",ani);
		
		//stand1
		ani = new Animation("stand1",interval);
		ani.addFrame("character_00002000_stand1_0_body.png");
		ani.addFrame("character_00002000_stand1_1_body.png");
		ani.addFrame("character_00002000_stand1_2_body.png");
		body.put("stand1",ani);
		
		ani = new Animation("stand1",interval);
		ani.addFrame("character_00002000_stand1_0_arm.png");
		ani.addFrame("character_00002000_stand1_1_arm.png");
		ani.addFrame("character_00002000_stand1_2_arm.png");
		arm.put("stand1",ani);
		
		//stand2
		ani = new Animation("stand2",interval);
		ani.addFrame("character_00002000_stand2_0_body.png");
		ani.addFrame("character_00002000_stand2_1_body.png");
		ani.addFrame("character_00002000_stand2_2_body.png");
		body.put("stand2",ani);
		
		ani = new Animation("stand2",interval);
		ani.addFrame("character_00002000_stand2_0_arm.png");
		ani.addFrame("character_00002000_stand2_1_arm.png");
		ani.addFrame("character_00002000_stand2_2_arm.png");
		arm.put("stand2",ani);
		
		//swingo1
		ani = new Animation("swingo1",interval);
		ani.addFrame("character_00002000_swingo1_0_body.png");
		ani.addFrame("character_00002000_swingo1_1_body.png");
		ani.addFrame("character_00002000_swingo1_2_body.png");
		body.put("swingo1",ani);
		
		ani = new Animation("swingo1",interval);
		ani.addFrame("character_00002000_swingo1_0_arm.png");
		ani.addFrame("character_00002000_swingo1_1_arm.png");
		ani.addFrame("character_00002000_swingo1_2_arm.png");
		arm.put("swingo1",ani);
		
		//swingo2
		ani = new Animation("swingo2",interval);
		ani.addFrame("character_00002000_swingo2_0_body.png");
		ani.addFrame("character_00002000_swingo2_1_body.png");
		ani.addFrame("character_00002000_swingo2_2_body.png");
		body.put("swingo2",ani);
		
		ani = new Animation("swingo2",interval);
		ani.addFrame("character_00002000_swingo2_0_arm.png");
		ani.addFrame("character_00002000_swingo2_1_arm.png");
		ani.addFrame("character_00002000_swingo2_2_arm.png");
		arm.put("swingo2",ani);
		
		//swingo3
		ani = new Animation("swingo3",interval);
		ani.addFrame("character_00002000_swingo3_0_body.png");
		ani.addFrame("character_00002000_swingo3_1_body.png");
		ani.addFrame("character_00002000_swingo3_2_body.png");
		body.put("swingo3",ani);
		
		ani = new Animation("swingo3",interval);
		ani.addFrame("character_00002000_swingo3_0_arm.png");
		ani.addFrame("character_00002000_swingo3_1_arm.png");
		ani.addFrame("character_00002000_swingo3_2_arm.png");
		arm.put("swingo3",ani);
		
		//swingof
		ani = new Animation("swingof",interval);
		ani.addFrame("character_00002000_swingof_0_body.png");
		ani.addFrame("character_00002000_swingof_1_body.png");
		ani.addFrame("character_00002000_swingof_2_body.png");
		body.put("swingof",ani);
		
		ani = new Animation("swingof",interval);
		ani.addFrame("character_00002000_swingof_0_arm.png");
		ani.addFrame("character_00002000_swingof_1_arm.png");
		ani.addFrame("character_00002000_swingof_2_arm.png");
		arm.put("swingof",ani);
	
		//swingp1
		ani = new Animation("swingp1",interval);
		ani.addFrame("character_00002000_swingp1_0_body.png");
		ani.addFrame("character_00002000_swingp1_1_body.png");
		ani.addFrame("character_00002000_swingp1_2_body.png");
		body.put("swingp1",ani);
		
		ani = new Animation("swingp1",interval);
		ani.addFrame("character_00002000_swingp1_0_arm.png");
		ani.addFrame("character_00002000_swingp1_1_arm.png");
		ani.addFrame("character_00002000_swingp1_2_arm.png");
		arm.put("swingp1",ani);
		
		//swingp2
		ani = new Animation("swingp2",interval);
		ani.addFrame("character_00002000_swingp2_0_body.png");
		ani.addFrame("character_00002000_swingp2_1_body.png");
		ani.addFrame("character_00002000_swingp2_2_body.png");
		body.put("swingp2",ani);
		
		ani = new Animation("swingp2",interval);
		ani.addFrame("character_00002000_swingp2_0_arm.png");
		ani.addFrame("character_00002000_swingp2_1_arm.png");
		ani.addFrame("character_00002000_swingp2_2_arm.png");
		arm.put("swingp2",ani);
		
		//swingpf
		ani = new Animation("swingpf",interval);
		ani.addFrame("character_00002000_swingpf_0_body.png");
		ani.addFrame("character_00002000_swingpf_1_body.png");
		ani.addFrame("character_00002000_swingpf_2_body.png");
		ani.addFrame("character_00002000_swingpf_3_body.png");
		body.put("swingpf",ani);
		
		ani = new Animation("swingpf",interval);
		ani.addFrame("character_00002000_swingpf_0_arm.png");
		ani.addFrame("character_00002000_swingpf_1_arm.png");
		ani.addFrame("character_00002000_swingpf_2_arm.png");
		ani.addFrame("character_00002000_swingpf_3_arm.png");
		arm.put("swingpf",ani);
		
		ani = new Animation("swingpf",interval);
		ani.addFrame("character_00002000_swingpf_0_hand.png");
		ani.addFrame("character_00002000_swingpf_1_hand.png");
		ani.addFrame("character_00002000_swingpf_2_hand.png");
		ani.addFrame("character_00002000_swingpf_3_hand.png");
		hand.put("swingpf",ani);
		
		//swingt1
		ani = new Animation("swingt1",interval);
		ani.addFrame("character_00002000_swingt10_body.png");
		ani.addFrame("character_00002000_swingt1_1_body.png");
		ani.addFrame("character_00002000_swingt1_2_body.png");
		body.put("swingt1",ani);
		
		ani = new Animation("swingt1",interval);
		ani.addFrame("character_00002000_swingt1_0_arm.png");
		ani.addFrame("character_00002000_swingt1_1_arm.png");
		ani.addFrame("character_00002000_swingt1_2_arm.png");
		arm.put("swingt1",ani);
		
		ani = new Animation("swingt1",interval);
		ani.addFrame("character_00002000_swingt1_0_armoverhair.png");
		ani.addFrame("character_00002000_swingt1_1_armoverhair.png");
		ani.addFrame("character_00002000_swingt1_2_armoverhair.png");
		armoverhair.put("swingt1",ani);
		
		//swingt2
		ani = new Animation("swingt2",interval);
		ani.addFrame("character_00002000_swingt2_0_body.png");
		ani.addFrame("character_00002000_swingt2_1_body.png");
		ani.addFrame("character_00002000_swingt2_2_body.png");
		body.put("swingt2",ani);
		
		ani = new Animation("swingt2",interval);
		ani.addFrame("character_00002000_swingt2_0_arm.png");
		ani.addFrame("character_00002000_swingt2_1_arm.png");
		ani.addFrame("character_00002000_swingt2_2_arm.png");
		arm.put("swingt2",ani);
		
		//swingt3
		ani = new Animation("swingt3",interval);
		ani.addFrame("character_00002000_swingt3_0_body.png");
		ani.addFrame("character_00002000_swingt3_1_body.png");
		ani.addFrame("character_00002000_swingt3_2_body.png");
		body.put("swingt3",ani);
		
		ani = new Animation("swingt3",interval);
		ani.addFrame("character_00002000_swingt3_0_arm.png");
		ani.addFrame("character_00002000_swingt3_1_arm.png");
		ani.addFrame("character_00002000_swingt3_2_arm.png");
		arm.put("swingt3",ani);
		
		//swingtf
		ani = new Animation("swingtf",interval);
		ani.addFrame("character_00002000_swingtf_0_body.png");
		ani.addFrame("character_00002000_swingtf_1_body.png");
		ani.addFrame("character_00002000_swingtf_2_body.png");
		body.put("swingtf",ani);
		
		ani = new Animation("swingtf",interval);
		ani.addFrame("character_00002000_swingtf_0_arm.png");
		ani.addFrame("character_00002000_swingtf_1_arm.png");
		ani.addFrame("character_00002000_swingtf_2_arm.png");
		arm.put("swingtf",ani);
		
		//walk1
		ani = new Animation("walk1",interval);
		ani.addFrame("character_00002000_walk1_0_body.png");
		ani.addFrame("character_00002000_walk1_1_body.png");
		ani.addFrame("character_00002000_walk1_2_body.png");
		ani.addFrame("character_00002000_walk1_3_body.png");
		body.put("walk1",ani);
		
		ani = new Animation("walk1",interval);
		ani.addFrame("character_00002000_walk1_0_arm.png");
		ani.addFrame("character_00002000_walk1_1_arm.png");
		ani.addFrame("character_00002000_walk1_2_arm.png");
		ani.addFrame("character_00002000_walk1_3_arm.png");
		arm.put("walk1",ani);
		
		//walk2
		ani = new Animation("walk2",interval);
		ani.addFrame("character_00002000_walk2_0_body.png");
		ani.addFrame("character_00002000_walk2_1_body.png");
		ani.addFrame("character_00002000_walk2_2_body.png");
		ani.addFrame("character_00002000_walk2_3_body.png");
		body.put("walk2",ani);
		
		ani = new Animation("walk2",interval);
		ani.addFrame("character_00002000_walk2_0_arm.png");
		ani.addFrame("character_00002000_walk2_1_arm.png");
		ani.addFrame("character_00002000_walk2_2_arm.png");
		ani.addFrame("character_00002000_walk2_3_arm.png");
		arm.put("walk2",ani);
		
		ani = new Animation("walk2",interval);
		ani.addFrame("character_00002000_walk2_0_hand.png");
		ani.addFrame("character_00002000_walk2_1_hand.png");
		ani.addFrame("character_00002000_walk2_2_hand.png");
		ani.addFrame("character_00002000_walk2_3_hand.png");
		hand.put("walk2",ani);
	}
}
