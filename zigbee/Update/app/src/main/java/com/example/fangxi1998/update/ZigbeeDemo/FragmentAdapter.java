package com.example.fangxi1998.update.ZigbeeDemo;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;

import android.support.v4.app.FragmentPagerAdapter;

import com.example.fangxi1998.update.backup.three;

public class FragmentAdapter extends FragmentPagerAdapter {

    private Fragment fragment1,fragment2,fragment3;

    public FragmentAdapter(FragmentManager fm) {
        super(fm);
        fragment1=new HomeActivity();
        fragment2=new MonitorActivity();
        fragment3=new three();


    }

    @Override
    public Fragment getItem(int i) {
        Fragment fragment=null;
        switch (i){
            case 0:
                fragment=fragment1;
                break;
            case 1:
                fragment=fragment2;

                break;
            case 2:
                fragment=fragment3;
                break;


        }
        return fragment;
    }

    @Override
    public int getCount() {
        return 3;
    }
}
