// import axios from "axios";
import { $ } from "./axios.ts";
// import { useQuery } from "@tanstack/react-query";
// import { useQuery, useMutation, useQueryClient } from "@tanstack/react-query";
// import { ReactQueryDevtools } from "@tanstack/react-query-devtools/production";
import { User } from "./User.ts";
import { Content } from "./Content.ts";
// import { startTransition, useState } from "react";

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

// export function sendFile(file: File) {
//   const { user } = useUserStore();

//   const formData = new FormData();
//   formData.append("user_id", user!.user_id.toString()); // Append userId
//   formData.append("content", file); // Append the file

//   const fetchData = async (): Promise<Content> => {
//     const response = await $.post(`/api/chatroom/files`, {
//       Headers: {
//         "Content-Type": "multipart/form-data",
//       },
//       data: formData,
//     }).then((res) => res.data);
//     console.log(response);

//     return response;
//   };
// setFile(null);
// file = null;
//   return fetchData;
// }

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
