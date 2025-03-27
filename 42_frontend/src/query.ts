import { $ } from "./axios.ts";
import { User } from "./User.ts";
import { Content } from "./Content.ts";

export interface chatting {
  users: User[];
  contents: Content[];
}

export const getChattingList = async (): Promise<chatting> => {
  const res = await $.get(`/api/chatroom`);
  console.log(res);
  return res.data;
  //     if (localStorage.getItem("SessionId")) {}
};

export function deleteFile(contentId: number) {
  const fetchData = async (): Promise<Content> => {
    const response = await $.delete(`/api/chatroom/files/${contentId}`).then(
      (res) => res.data
    );
    console.log(response);
    return response;
  };
  return fetchData();
}

export function deleteComments(contentId: number) {
  const fetchData = async (): Promise<Content> => {
    const response = await $.delete(`/api/chatroom/comments/${contentId}`).then(
      (res) => res.data
    );
    return response;
    console.log(response);
  };
  return fetchData();
}
