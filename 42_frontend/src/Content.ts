// import { useEffect } from "react";
import { create } from "zustand";

export interface Content {
  user_id: string;
  content_id: number;
  user_name: number;
  content: string;
  is_exist: boolean;
  is_comment: boolean;
  timestamp: string;
}

export interface ContentStore {
  contents: Content[];
  addContent: (content: Content) => void;
  setContents: (contents: Content[]) => void;
  oldContents: Content[];
  setOldContents: (oldContents: Content[]) => void;
  recentContents: Content[];
  setRecentContents: (oldContents: Content[]) => void;
  // deletedContents: Content[];
  // setDeletedContents: (deletedContents: Content[]) => void;
}

export const useContentStore = create<ContentStore>((set) => ({
  contents: [],
  addContent: (content) =>
    set((state) => ({ contents: [...state.contents, content] })),
  setContents: (contents) => set({ contents: contents }),
  oldContents: [],
  setOldContents: (contents) => set({ oldContents: contents }),
  recentContents: [],
  setRecentContents: (contents) => set({ recentContents: contents }),
  // deletedContents: [],
  // setDeletedContents: (contents) => set({ deletedContents: contents }),
}));

export default useContentStore;
